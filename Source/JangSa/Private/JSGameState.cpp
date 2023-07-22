// Fill out your copyright notice in the Description page of Project Settings.


#include "JSGameState.h"

#include "JSGameSingleton.h"
#include "Card/JSCardFactory.h"
#include "Card/JSCard.h"
#include "Card/JSCardSlot.h"
#include "Data/JSTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/JSTurnEventManager.h"
#include "UI/JSHUD.h"
#include "Math/UnrealMathUtility.h"

AJSGameState::AJSGameState()
{
	PlayerData = new FPlayerData();
	GetPlayerData()->CurrentStage = 0;
}

void AJSGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	for (int ix = 0; ix < 49; ix++)
	{
		ActivatedCards.Emplace(nullptr);
	}

	if (nullptr != CardFactoryRef)
	{
		CardActorFactory = NewObject<UJSCardFactory>(GetWorld(), CardFactoryRef);
		CardActorFactory->InitFactory();
	}

	TurnManager = GetWorld()->SpawnActor<AJSTurnEventManager>(TurnManagerClass);

	GetPlayerData()->CurrentStage = -1;
}

void AJSGameState::SetRemainTurn(const int32 InRemainTurn)
{
	UE_LOG(LogTemp, Log, TEXT("Set Remain Turn"));
	if (InRemainTurn <= 0)
	{
		if (!AddCurrentCarat(-GetPlayerData()->PayCarat))
		{
			AJSHUD* JSHud = Cast<AJSHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			if (nullptr != JSHud)
			{
				JSHud->ShowDefeatWidget();
			}
			GamePlayState = EGamePlayState::Finished;

			return;
		}

		// Game End If Current Stage is Last Stage
		if (GetPlayerData()->CurrentStage == UJSGameSingleton::Get().GetMaxTurnCount())
		{
			AJSHUD* JSHud = Cast<AJSHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			if (nullptr != JSHud)
			{
				JSHud->ShowResultInfoWidget(*GetPlayerData());
			}
			GamePlayState = EGamePlayState::Finished;

			return;
		}

		// Set To Next Phase
		GetPlayerData()->CurrentStage += 1;
		
		SetPayTurn(UJSGameSingleton::Get().GetTurnInfo(GetPlayerData()->CurrentStage).InitPhaseTurn);
		SetPayCarat(UJSGameSingleton::Get().GetTurnInfo(GetPlayerData()->CurrentStage).PayCarat);
		GetPlayerData()->RemainTurn = UJSGameSingleton::Get().GetTurnInfo(GetPlayerData()->CurrentStage).InitPhaseTurn;
		NotifyRemainTurn.Broadcast(GetPlayerData()->RemainTurn);

		RefreshPlayerInfo();

		OnCheckEventQueue();

		return;
	}

	GetPlayerData()->RemainTurn = InRemainTurn;
	NotifyRemainTurn.Broadcast(GetPlayerData()->RemainTurn);

	ActivateHandler.Invalidate();
	GetWorld()->GetTimerManager().SetTimer(ActivateHandler, this, &AJSGameState::OnEnterStartTurn, .1f, false,
	                                       1.5f);
	NotifyPlayerControllerState.Broadcast(EPlayerControllerState::Disabled);
}

void AJSGameState::RefreshPlayerInfo() const
{
	NotifyPayCarat.Broadcast(GetPlayerData()->PayCarat);
	NotifyPayTurn.Broadcast(GetPlayerData()->PayTurn);
	NotifyCurrentCarat.Broadcast(GetPlayerData()->CurrentCarat);
	NotifyRemainTurn.Broadcast(GetPlayerData()->RemainTurn);
}

void AJSGameState::DprGameStart()
{
	UE_LOG(LogTemp, Log, TEXT("Game Start"));

	GamePlayState = EGamePlayState::Playing;

	SetRemainTurn(-1);

	// Spawn Slot
	const FVector StartSlotSpawnPosition(255.0f, 470.0f, 93.5f);
	for (int ix = 0; ix < (MAX_SLOT_NUM * MAX_SLOT_NUM); ix++)
	{
		FVector CurSlotSpawnPosition = StartSlotSpawnPosition;
		CurSlotSpawnPosition += FVector(0.f, -10.f, 0.f) * (ix % MAX_SLOT_NUM);
		CurSlotSpawnPosition += FVector(-10.f, 0.f, 0.f) * (ix / MAX_SLOT_NUM);

		AJSCardSlot* NewSlot = Cast<AJSCardSlot>(GetWorld()->SpawnActor(CardSlot, &CurSlotSpawnPosition));
		NewSlot->InitSlot(ix);

		CardSlots.Emplace(NewSlot);
	}

	SpawnInitCard();
}

void AJSGameState::SpawnInitCard()
{
	UE_LOG(LogTemp, Log, TEXT("Spawn Init Card"));

	for (auto StartCardInfo : UJSGameSingleton::Get().GetStartCardInfos())
	{
		FVector SpawnLocation(265.0f, 400.0f, 93.1f);

		AJSCard* NewCardActor = Cast<AJSCard>(CardActorFactory->SpawnCardActor(StartCardInfo->Id, &SpawnLocation));

		if (StartCardInfo->FieldNum >= 0)
		{
			FVector SlotPos;
			HoldingCards.Emplace(NewCardActor);
			RegisterActivateCard(NewCardActor, StartCardInfo->FieldNum, SlotPos);
			//	NewCardActor->SetActorLocation(SlotPos + FVector(0.f, 0.f, 1.f));
		}
		else
		{
			InventoryCards.Emplace(NewCardActor);
		}
	}

	ArrangeCard();
}

void AJSGameState::OnEnterStartTurn()
{
	UE_LOG(LogTemp, Log, TEXT("On Enter Start Turn"));

	if (GamePlayState != EGamePlayState::Playing)
		return;

	NotifyPlayerControllerState.Broadcast(EPlayerControllerState::Interactable);

	ShuffleHoldingCards();
	OnResetShop();
}

void AJSGameState::ShuffleHoldingCards()
{
	const int32 MaxHoldingPack = 10;

	// Send Holding Cards to Inventory
	while (HoldingCards.Num() > 0)
	{
		AJSCard* CardActor = HoldingCards[0];
		HoldingCards.RemoveAt(0);
		InventoryCards.Emplace(CardActor);
		CardActor->SetCardState(ECardState::Inventory);
	}

	// Send Inventory Cards to hold
	for (int ix = 0; ix < MaxHoldingPack; ix++)
	{
		if (InventoryCards.Num() <= 0)
		{
			break;
		}

		int InCardIndex = FMath::RandRange(0, InventoryCards.Num() - 1);
		AJSCard* CardActor = InventoryCards[InCardIndex];
		InventoryCards.RemoveAt(InCardIndex);
		HoldingCards.Emplace(CardActor);
		CardActor->SetCardState(ECardState::Holding);
	}

	ArrangeCard();
}


void AJSGameState::OnCheckEventQueue()
{
	UE_LOG(LogTemp, Log, TEXT("On Check Event Queue"));

	NotifyPlayerControllerState.Broadcast(EPlayerControllerState::Disabled);

	NotifyCheckEvent.Broadcast(GetPlayerData()->CurrentStage);
}

void AJSGameState::OnResetShop(bool bIsInitTurn) 
{
	UE_LOG(LogTemp, Log, TEXT("On Reset Shop"));

	if (!bIsInitTurn)
	{
		// To do : Check to pay
		if(!AddCurrentCarat(-2))
			return;
	}

	NotifyPlayerControllerState.Broadcast(EPlayerControllerState::Disabled);

	TArray<FCardInfoData*> CardInfoDatas = CardActorFactory->SpawnCardActorOnShop();

	AJSHUD* JSHud = Cast<AJSHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (nullptr != JSHud)
	{
		JSHud->InitializeShop(CardInfoDatas, bIsInitTurn);
	}
}

void AJSGameState::FoldShop(bool bIsFolded)
{
	if (bIsFolded)
	{
		NotifyPlayerControllerState.Broadcast(EPlayerControllerState::Disabled);
	}
	else
	{
		NotifyPlayerControllerState.Broadcast(EPlayerControllerState::Interactable);
	}
}

void AJSGameState::ExitShop()
{
	NotifyPlayerControllerState.Broadcast(EPlayerControllerState::Selectable);

	AJSHUD* JSHud = Cast<AJSHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (nullptr != JSHud)
	{
		JSHud->EnableTurnEndButton();
	}
}

bool AJSGameState::PurchaseCard(int32 InCardNum)
{
	const int32 CardPrice = CardActorFactory->CheckCardPrice(InCardNum);

	// To Do : if(GetPlayerData()->CurrentCarat >= CardPrice);
	if (AddCurrentCarat(-CardPrice))
	{
		// To Do : Pay Owning Carat
		const FVector SpawnLocation(265.0f, 400.0f, 93.1f);

		AJSCard* NewCardActor = Cast<AJSCard>(CardActorFactory->SpawnCardActor(InCardNum, &SpawnLocation));

		if (NewCardActor != nullptr)
		{
			InventoryCards.Emplace(NewCardActor);

			GetPlayerData()->PurchasedCard++;

			ArrangeCard();

			return true;
		}
	}

	return false;
}

void AJSGameState::OnExitTurn()
{
	UE_LOG(LogTemp, Log, TEXT("On Exit Turn"));

	OnEnterSettleCaratPhase();
}

void AJSGameState::OnEnterSettleCaratPhase()
{
	UE_LOG(LogTemp, Log, TEXT("On Enter Settle Carat"));

	int ActivationNum = 0;

	// Activate Each Card Effects
	for (auto Card : ActivatedCards)
	{
		if (Card == nullptr)
		{
			continue;
		}

		Card->ActivateCardEffect(0);
		ActivationNum += 1;
	}

	AddRemainTurn(-1);
}

bool AJSGameState::RegisterActivateCard(AJSCard* InCard, int32 SlotNum, FVector& SlotPosition)
{
	if (SlotNum >= 49)
	{
		return false;
	}

	if (!HoldingCards.Contains(InCard))
	{
		return false;
	}

	if (ActivatedCards[SlotNum] != nullptr)
	{
		return false;
	}

	HoldingCards.Remove(InCard);
	ActivatedCards[SlotNum] = InCard;

	SlotPosition = CardSlots[SlotNum]->GetActorLocation() + FVector(0.f, 0.f, 5.f);
	InCard->SetActorLocation(SlotPosition);

	CardSlots[SlotNum]->RegisterCard();
	//AddTurnResultCarat(InCard->GetResultCarat());

	ArrangeCard();

	return true;
}

bool AJSGameState::UnregisterActivateCard(AJSCard* InCard)
{
	if (!ActivatedCards.Contains(InCard)) return false;

	UE_LOG(LogTemp, Log, TEXT("UnRegister Card"));

	const int32 CardIndex = ActivatedCards.Find(InCard);

	HoldingCards.Emplace(InCard);
	ActivatedCards[CardIndex] = nullptr;

	AddTurnResultCarat(-InCard->GetResultCarat());

	ArrangeCard();

	return true;
}

void AJSGameState::ArrangeCard()
{
	// Arrange Holding Cards
	FVector HoldingSpawnLocation(265.0f, 440.0f, 95.f);
	HoldingSpawnLocation += FVector(.0, 3.0f, .0f) * (HoldingCards.Num() - 1);
	for (int ix = 0; ix < HoldingCards.Num(); ix++)
	{
		HoldingCards[ix]->SetActorLocation(HoldingSpawnLocation + (FVector(.0, -6.0f, .0f) * ix));
		HoldingCards[ix]->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	}

	// Arrange Inventory Cards
	const FVector InventorySpawnLocation(230.0f, 390.0f, 105.f);
	for (int ix = 0; ix < InventoryCards.Num(); ix++)
	{
		InventoryCards[ix]->SetActorLocation(InventorySpawnLocation);
	}
}

AJSTurnEventManager* AJSGameState::GetTurnManager() const
{
	if (nullptr != TurnManager)
	{
		return Cast<AJSTurnEventManager>(TurnManager);
	}

	return nullptr;
}

TArray<AJSCard*> AJSGameState::CardsInCondition(const FString InRank)
{
	TArray<AJSCard*> CardArray;

	for (auto CardActor : ActivatedCards)
	{
		if (nullptr == CardActor)
		{
			continue;
		}

		if (CardActor->GetCardInfo().Rank.Contains(InRank))
		{
			CardArray.Emplace(CardActor);
		}
	}

	return CardArray;
}

int32 AJSGameState::CountCardInCardNum(int32 InCardNum)
{
	int32 Count = 0;
	for (auto CardActor : ActivatedCards)
	{
		if (nullptr == CardActor)
		{
			continue;
		}

		if (CardActor->GetCardInfo().Id == InCardNum)
		{
			Count += 1;
		}
	}
	return Count;
}

int32 AJSGameState::CountCardInCardCharacteristics(FString InCharacteristics)
{
	int32 Count = 0;
	for (auto CardActor : ActivatedCards)
	{
		if (nullptr == CardActor)
		{
			continue;
		}

		if (CardActor->GetCardInfo().Characteristic1.Contains(InCharacteristics) || CardActor->GetCardInfo().
			Characteristic2.
			Contains(InCharacteristics))
		{
			Count += 1;
		}
	}
	return Count;
}

int32 AJSGameState::CountCardInCardRank(FString InCardRank)
{
	int32 Count = 0;
	for (const auto Card : ActivatedCards)
	{
		if (Card->GetCardInfo().Rank.Contains(InCardRank))
		{
			Count += 1;
		}
	}
	return Count;
}
