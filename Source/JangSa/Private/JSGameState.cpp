// Fill out your copyright notice in the Description page of Project Settings.


#include "JSGameState.h"
#include "JSCardFactory.h"
#include "JSGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "Card/JSCard.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/JSRenderManager.h"
#include "UI/JSHUD.h"

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
		GetPlayerData()->PayCarat = TurnInfoDatas[GetPlayerData()->CurrentStage]->PayCarat;

		GetPlayerData()->RemainTurn = TurnInfoDatas[GetPlayerData()->CurrentStage]->InitPhaseTurn;

		return;
	}

	GetPlayerData()->RemainTurn = InRemainTurn;
}

void AJSGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UE_LOG(LogTemp, Log, TEXT("Total Turn Info : %d"), TurnInfoDatas.Num());
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Cyan, FString::FromInt(233));

	CardActorFactory = NewObject<UJSCardFactory>(GetWorld(), UJSCardFactory::StaticClass());
}

void AJSGameState::SetNextTurn()
{
	UE_LOG(LogTemp, Log, TEXT("======================================="));

	OnEnterStartTurn();
}

void AJSGameState::SetNextPhase()
{
}

bool AJSGameState::PurchaseCard(int32 InCardNum)
{
	UE_LOG(LogTemp, Log, TEXT("Purchased!!"));

	int32 CardPrice = CardActorFactory->CheckCardPrice(InCardNum);

	// To Do : if(GetPlayerData()->CurrentCarat >= CardPrice);
	if(CardPrice > 0)
	{
		// To Do : Pay Owning Carat


		CardActorFactory->SpawnCardActor(InCardNum);

		return true;
	}
	else
	{
		return false;
	}
}

void AJSGameState::OnCheckEventQueue()
{
}


void AJSGameState::OnEnterStartTurn()
{
	OnResetShop();
}


void AJSGameState::OnResetShop()
{
	// Reset Shop
	UE_LOG(LogTemp, Log, TEXT("Reset Shop..."));

	TArray<FCardInfoData*> CardInfoDatas = CardActorFactory->SpawnCardActorOnShop();

	AJSHUD* JSHud = Cast<AJSHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	JSHud->InitializeShop(CardInfoDatas);

	OnEnterUserControlTurn();
}

void AJSGameState::OnEnterUserControlTurn()
{
	// Keep phase state until TurnEnd button clicked
	OnExitTurn();
}

void AJSGameState::OnExitTurn()
{
	OnEnterSettleCarat();
}

void AJSGameState::OnEnterSettleCarat()
{
	CheckSynergy();

	// Activate Each Card Effects
	NotifyActivateCardEffect.Broadcast(0);

	// Reduce Each Activated Card Turns
	NotifyAddRemainCardTurn.Broadcast(-1);

	AddRemainTurn(-1);

	// If Each Card's remain turn come to zero, Destroy
	NotifyDestroyCard.Broadcast();

	//OnEnterStartTurn();
}

void AJSGameState::CheckSynergy()
{
}
