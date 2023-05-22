// Fill out your copyright notice in the Description page of Project Settings.


#include "JSGameState.h"
#include "Card/JSCardFactory.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "Card/JSCard.h"
#include "Data/JSTypes.h"
#include "Kismet/GameplayStatics.h"
#include "UI/JSHUD.h"
#include "Math/UnrealMathUtility.h"

AJSGameState::AJSGameState()
{
	PlayerData = new FPlayerData();
	GetPlayerData()->CurrentStage = 0;

	const ConstructorHelpers::FObjectFinder<UDataTable> DT_TurnDateTable(
		TEXT("/Game/DataTable/DT_TurnInfo.DT_TurnInfo"));
	if (DT_TurnDateTable.Succeeded())
	{
		DT_TurnDateTable.Object->GetAllRows<FTurnInfoData>(TEXT("GetAllRows"), TurnInfoDatas);
	}

	SetPayTurn(TurnInfoDatas[GetPlayerData()->CurrentStage]->InitPhaseTurn);
	SetRemainTurn(GetPlayerData()->PayTurn);
	GetPlayerData()->PayCarat = TurnInfoDatas[GetPlayerData()->CurrentStage]->PayCarat;
}

void AJSGameState::SetRemainTurn(const int32 InRemainTurn)
{
	// Deprecated Logv 
	UE_LOG(LogTemp, Log, TEXT("CurrentStage : %d"), GetPlayerData()->CurrentStage);

	if (InRemainTurn <= 0)
	{
		// Set To Next Phase
		GetPlayerData()->CurrentStage += 1;

		if (GetPlayerData()->CurrentStage == TurnInfoDatas.Num())
		{
			UE_LOG(LogTemp, Log, TEXT("!!!Game Clear!!!"));

			GamePlayState = EGamePlayState::Finished;

			return;
		}

		SetPayTurn(TurnInfoDatas[GetPlayerData()->CurrentStage]->InitPhaseTurn);
		SetPayCarat(TurnInfoDatas[GetPlayerData()->CurrentStage]->PayCarat);
		GetPlayerData()->RemainTurn = TurnInfoDatas[GetPlayerData()->CurrentStage]->InitPhaseTurn;

		return;
	}

	GetPlayerData()->RemainTurn = InRemainTurn;
	NotifyRemainTurn.Broadcast(GetPlayerData()->RemainTurn);
}

void AJSGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CardActorFactory = NewObject<UJSCardFactory>(GetWorld(), UJSCardFactory::StaticClass());
}

void AJSGameState::DprGameStart()
{
	UE_LOG(LogTemp, Log, TEXT("======================================="));
	RefreshPlayerInfo();

	AddCurrentCarat(15);
	
	OnEnterStartTurn();
}

void AJSGameState::SetNextPhase()
{
}

bool AJSGameState::PurchaseCard(int32 InCardNum)
{
	int32 CardPrice = CardActorFactory->CheckCardPrice(InCardNum);

	// To Do : if(GetPlayerData()->CurrentCarat >= CardPrice);
	if (AddCurrentCarat(-CardPrice))
	{
		// To Do : Pay Owning Carat
		FVector SpawnLocation(265.0f, 400.0f, 93.1f);

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

void AJSGameState::OnEnterStartTurn()
{
	ShuffleHoldingCards();
	
	OnCheckEventQueue();
}

void AJSGameState::ShuffleHoldingCards()
{
	int32 MaxHoldingPack = 10;

	// Send Holding Cards to Inventory
	while(HoldingCards.Num() > 0)
	{
		AJSCard* CardActor = HoldingCards[0];
		HoldingCards.RemoveAt(0);
		InventoryCards.Emplace(CardActor);
		CardActor->CardState = ECardState::Inventory;
	}

	// Send Inventory Cards to hold
	for(int ix = 0; ix < MaxHoldingPack; ix++)
	{
		if(InventoryCards.Num() <= 0)
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
	OnResetShop();
}

void AJSGameState::OnResetShop(bool bIsInitTurn)
{
	if (!bIsInitTurn)
	{
		// To do : Check to pay

		//return;
	}

	// Reset Shop
	UE_LOG(LogTemp, Log, TEXT("Reset Shop..."));

	TArray<FCardInfoData*> CardInfoDatas = CardActorFactory->SpawnCardActorOnShop();

	AJSHUD* JSHud = Cast<AJSHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (nullptr != JSHud)
	{
		JSHud->InitializeShop(CardInfoDatas);
	}
}

void AJSGameState::RefreshPlayerInfo() const
{
	NotifyPayCarat.Broadcast(GetPlayerData()->PayCarat);
	NotifyPayTurn.Broadcast(GetPlayerData()->PayTurn);
	NotifyCurrentCarat.Broadcast(0);
	NotifyRemainTurn.Broadcast(GetPlayerData()->RemainTurn);
}

void AJSGameState::RegisterCard(AJSCard* InCard)
{
	if(!HoldingCards.Contains(InCard))
		return;

	HoldingCards.Remove(InCard);
	ActivatedCards.Emplace(InCard);
}

void AJSGameState::ArrangeCard()
{
	// Arrange Holding Cards
	FVector HoldingSpawnLocation(265.0f, 440.0f, 95.f);
	HoldingSpawnLocation += FVector(.0, 3.0f, .0f) * (HoldingCards.Num() - 1); 
	for(int ix = 0; ix < HoldingCards.Num(); ix++)
	{
		HoldingCards[ix]->SetActorLocation(HoldingSpawnLocation + (FVector(.0, -6.0f, .0f) * ix));
	}

	// Arrange Inventory Cards
	const FVector InventorySpawnLocation(265.0f, 400.0f, 93.1f);
	const int32 InventoryRow = 3;
	for(int ix = 0; ix < InventoryCards.Num(); ix++)
	{
		FVector OffsetVector = (ix / InventoryRow) * FVector(-6.f, 0.f, 0.f);
		OffsetVector += (ix % InventoryRow) * FVector(.0f, -6.f, .0f);
		InventoryCards[ix]->SetActorLocation(InventorySpawnLocation + OffsetVector);
	}
}

void AJSGameState::OnExitTurn()
{
	OnEnterSettleCaratPhase();
}

void AJSGameState::OnEnterSettleCaratPhase()
{
	UE_LOG(LogTemp, Log, TEXT("Acitvation On Card State"));

	// Activate Each Card Effects
	for(auto Card : ActivatedCards)
	{
		Card->ActivateCardEffect(0);
		Card->AddRemainTurn(-1);
	}

	AddRemainTurn(-1);

	// If Each Card's remain turn come to zero, Destroy
	NotifyDestroyCard.Broadcast();

	OnEnterStartTurn();
}

void AJSGameState::SelectCard(AJSCard* InCard)
{
	if(SelectedCard != nullptr)
	{
		SelectedCard->SetPossessCard(false);
	}
	
	SelectedCard = InCard;
	SelectedCard->SetPossessCard(true);
}

TArray<AJSCard*> AJSGameState::CardsInCondition(const FString InRank)
{
	TArray<AJSCard*> CardArray;

	for(auto CardActor : ActivatedCards)
	{
		if(CardActor->GetCardInfo().Rank.Contains(InRank))
		{
			CardArray.Emplace(CardActor);
		}
	}

	return CardArray;
}
