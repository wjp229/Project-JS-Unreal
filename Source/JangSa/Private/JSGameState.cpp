// Fill out your copyright notice in the Description page of Project Settings.


#include "JSGameState.h"

#include "JSGameSingleton.h"
#include "Card/JSCardFactory.h"
#include "UObject/ConstructorHelpers.h"
#include "Card/JSCard.h"
#include "Card/JSCardSlot.h"
#include "Data/JSTypes.h"
#include "Kismet/GameplayStatics.h"
#include "UI/JSHUD.h"
#include "Math/UnrealMathUtility.h"

AJSGameState::AJSGameState()
{
	PlayerData = new FPlayerData();
	GetPlayerData()->CurrentStage = 0;
	
	const ConstructorHelpers::FClassFinder<AJSCardSlot> CardSlotRef(TEXT("/Script/JangSa.JSCardSlot"));
	if(nullptr != CardSlotRef.Class)
	{
		CardSlot = CardSlotRef.Class;
	}
}

void AJSGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	for(int ix = 0; ix < 49; ix++)
	{
		ActivatedCards.Emplace(nullptr);
	}
	
	CardActorFactory = NewObject<UJSCardFactory>(GetWorld(), UJSCardFactory::StaticClass());
	CardActorFactory->InitFactory();
}

void AJSGameState::SetRemainTurn(const int32 InRemainTurn)
{
	if (InRemainTurn <= 0)
	{
		if(!AddCurrentCarat(-GetPlayerData()->PayCarat))
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
			UE_LOG(LogTemp, Log, TEXT("!!!Game Clear!!!"));

			GamePlayState = EGamePlayState::Finished;

			return;
		}
		
		// Set To Next Phase
		GetPlayerData()->CurrentStage += 1;
		
		SetPayTurn(UJSGameSingleton::Get().GetTurnInfo(GetPlayerData()->CurrentStage).InitPhaseTurn);
		SetPayCarat(UJSGameSingleton::Get().GetTurnInfo(GetPlayerData()->CurrentStage).PayCarat);
		GetPlayerData()->RemainTurn = UJSGameSingleton::Get().GetTurnInfo(GetPlayerData()->CurrentStage).InitPhaseTurn;
		
		return;
	}

	GetPlayerData()->RemainTurn = InRemainTurn;
	NotifyRemainTurn.Broadcast(GetPlayerData()->RemainTurn);
}

void AJSGameState::RefreshPlayerInfo() const
{
	NotifyPayCarat.Broadcast(GetPlayerData()->PayCarat);
	NotifyPayTurn.Broadcast(GetPlayerData()->PayTurn);
	NotifyCurrentCarat.Broadcast(0);
	NotifyRemainTurn.Broadcast(GetPlayerData()->RemainTurn);
}

void AJSGameState::DprGameStart()
{
	UE_LOG(LogTemp, Log, TEXT("======================================="));
	
	SetPayTurn(UJSGameSingleton::Get().GetTurnInfo(GetPlayerData()->CurrentStage).InitPhaseTurn);
	SetRemainTurn(GetPlayerData()->PayTurn);
	GetPlayerData()->PayCarat = UJSGameSingleton::Get().GetTurnInfo(GetPlayerData()->CurrentStage).PayCarat;
	AddTurnResultCarat(0);
	
	RefreshPlayerInfo();

	AddCurrentCarat(15);

	const FVector StartSlotSpawnPosition(255.0f,470.0f,93.5f);
	// Spawn Slot
	for(int ix = 0; ix < (MAX_SLOT_NUM * MAX_SLOT_NUM); ix++)
	{
		FVector CurSlotSpawnPosition = StartSlotSpawnPosition;
		CurSlotSpawnPosition += FVector(0.f, -10.f, 0.f) * (ix % MAX_SLOT_NUM);
		CurSlotSpawnPosition += FVector(-10.f, 0.f, 0.f) * (ix / MAX_SLOT_NUM);
		
		AJSCardSlot* NewSlot = Cast<AJSCardSlot>(GetWorld()->SpawnActor(CardSlot, &CurSlotSpawnPosition));
		NewSlot->InitSlot(ix);

		CardSlots.Emplace(NewSlot);
	}

	SpawnInitCard();

	OnEnterStartTurn();
}

void AJSGameState::SpawnInitCard()
{
	for(auto StartCardInfo : UJSGameSingleton::Get().GetStartCardInfos())
	{
		FVector SpawnLocation(265.0f, 400.0f, 93.1f);

		AJSCard* NewCardActor = Cast<AJSCard>(CardActorFactory->SpawnCardActor(StartCardInfo->Id, &SpawnLocation));

		if(StartCardInfo->FieldNum >= 0)
		{
			FVector SlotPos;
			HoldingCards.Emplace(NewCardActor);
			RegisterActivateCard(NewCardActor, StartCardInfo->FieldNum, SlotPos);
			NewCardActor->SetActorLocation(SlotPos + FVector(0.f, 0.f, 1.f));
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
	ShuffleHoldingCards();

	OnCheckEventQueue();
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
		CardActor->CardState = ECardState::Inventory;
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
		CardActor->CardState = ECardState::Holding;
	}

	ArrangeCard();
}


void AJSGameState::OnCheckEventQueue()
{
	NotifyCheckEvent.Broadcast(GetPlayerData()->CurrentStage);

	UE_LOG(LogTemp, Log, TEXT("OnCheckEventQueue %d"), GetPlayerData()->CurrentStage);
	
}

void AJSGameState::OnResetShop(bool bIsInitTurn) const
{
	if (!bIsInitTurn)
	{
		// To do : Check to pay

		//return;
	}

	TArray<FCardInfoData*> CardInfoDatas = CardActorFactory->SpawnCardActorOnShop();

	AJSHUD* JSHud = Cast<AJSHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (nullptr != JSHud)
	{
		JSHud->InitializeShop(CardInfoDatas);
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

			ArrangeCard();

			return true;
		}
	}
	
	return false;
}

void AJSGameState::OnExitTurn()
{
	GetPlayerData()->CurrentStage += 1;
	
	OnEnterSettleCaratPhase();

}

void AJSGameState::OnEnterSettleCaratPhase()
{
	// Activate Each Card Effects
	for (auto Card : ActivatedCards)
	{
		if(Card == nullptr)
		{
			continue;
		}

		Card->ActivateCardEffect(0);
	}

	AddRemainTurn(-1);

	OnEnterStartTurn();
}

bool AJSGameState::RegisterActivateCard(AJSCard* InCard, int32 SlotNum, FVector& SlotPosition)
{
	if(SlotNum >= 49)
	{
		return false;
	}
	
	if (!HoldingCards.Contains(InCard))
	{
		return false;
	}

	if(ActivatedCards[SlotNum] != nullptr)
	{
		return false;
	}
	
	HoldingCards.Remove(InCard);
	ActivatedCards[SlotNum] = InCard;

	SlotPosition = CardSlots[SlotNum]->GetActorLocation();

	AddTurnResultCarat(InCard->GetResultCarat());

	ArrangeCard();
	
	return true;
}

bool AJSGameState::UnregisterActivateCard(AJSCard* InCard)
{
	if(!ActivatedCards.Contains(InCard)) return false;

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
	}

	// Arrange Inventory Cards
	const FVector InventorySpawnLocation(230.0f, 390.0f, 105.f);
	for (int ix = 0; ix < InventoryCards.Num(); ix++)
	{
		InventoryCards[ix]->SetActorLocation(InventorySpawnLocation);
	}
	// const int32 InventoryRow = 3;
	// for (int ix = 0; ix < InventoryCards.Num(); ix++)
	// {
	// 	FVector OffsetVector = (ix / InventoryRow) * FVector(-6.f, 0.f, 0.f);
	// 	OffsetVector += (ix % InventoryRow) * FVector(.0f, -6.f, .0f);
	// 	InventoryCards[ix]->SetActorLocation(InventorySpawnLocation + OffsetVector);
	// }

	// Arrange Active Cards
	// const FVector OffsetLocation(.0f, .0f, 5.f);
	//
	// for (int ix = 0; ix < ActivatedCards.Num(); ix++)
	// {
	// 	if(nullptr == ActivatedCards[ix])
	// 	{
	// 		continue;
	// 	}
	// 	
	// 	ActivatedCards[ix]->SetActorLocation(CardSlots[ix]->GetActorLocation() + OffsetLocation);
	// }
}

TArray<AJSCard*> AJSGameState::CardsInCondition(const FString InRank)
{
	TArray<AJSCard*> CardArray;

	for (auto CardActor : ActivatedCards)
	{
		if(nullptr == CardActor)
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
		if(nullptr == CardActor)
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
		if(nullptr == CardActor)
		{
			continue;
		}
		
		if (CardActor->GetCardInfo().Characteristic1.Contains(InCharacteristics) || CardActor->GetCardInfo().Characteristic2.
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
