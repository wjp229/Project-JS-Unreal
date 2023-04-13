// Fill out your copyright notice in the Description page of Project Settings.


#include "JSGameState.h"
#include "UObject/ConstructorHelpers.h"
#include "CardInfoRowBase.h"
#include "TurnInfoRowBase.h"
#include "Engine/DataTable.h"
#include "JSCard.h"
#include "JSCardActorFactory.h"

AJSGameState::AJSGameState()
{
	PlayerData = new FPlayerData();
	GetPlayerData()->CurrentStage = 0;

	const ConstructorHelpers::FObjectFinder<UDataTable> DT_TurnDateTable(TEXT("/Game/DataTable/DT_TurnInfo.DT_TurnInfo"));
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
	UE_LOG(LogTemp, Log, TEXT("Remain Turn : %d // Remain Carat : %d"), InRemainTurn, GetPlayerData()->PayCarat);
	
	if(InRemainTurn <= 0)
	{
		// Set To Next Phase
		GetPlayerData()->CurrentStage += 1;

		if(GetPlayerData()->CurrentStage == TurnInfoDatas.Num())
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

	UE_LOG(LogTemp, Log, TEXT("Actor Factory Created!!"));
	CardActorFactory = NewObject<UJSCardActorFactory>(this, UJSCardActorFactory::StaticClass());

	// {
	// 	const ConstructorHelpers::FObjectFinder<UDataTable> DT_CardDataTable(TEXT("/Game/DataTable/DT_CardInfo.DT_CardInfo"));
	// 	if (DT_CardDataTable.Succeeded())
	// 	{
	// 		DT_CardDataTable.Object->GetAllRows<FCardInfoData>(TEXT("GetAllRows"), CardInfoDatas);
	// 	}
	// 	
	// 	FCardData* CardData = new FCardData();
	// 	CardData->Name = CardInfoDatas[0]->Name;
	// 	CardData->Rank = CardInfoDatas[0]->Rank;
	// 	CardData->bCanControlByUser = CardInfoDatas[0]->CanControlByUser;
	// 	CardData->InitRemainTurn = CardInfoDatas[0]->InitRemainTurn;
	// 	CardData->bShowOnShop = CardInfoDatas[0]->ShowOnShop;
	// 	CardData->Price = CardInfoDatas[0]->Price;
	// 	CardData->Probability = CardInfoDatas[0]->Probability;
	// 	CardData->Description = CardInfoDatas[0]->Description;
	//
	// 	AJSCard* TempCard = NewObject<AJSCard>(this, AJSCard::StaticClass());
	// 	TempCard->InitCard(CardData);
	// 	
	// 	UE_LOG(LogTemp, Log, TEXT("Card has been created!!"));
	// }
}

void AJSGameState::SetNextTurn()
{
	UE_LOG(LogTemp, Log, TEXT("======================================="));
	
	OnEnterStartTurn();
}

void AJSGameState::SetNextPhase()
{

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

	CardActorFactory->SpawnCardActorOnShop();
	
	OnEnterUserControlTurn();
}

void AJSGameState::OnEnterUserControlTurn()
{
	// Keep phase state until TurnEnd button clicked
	UE_LOG(LogTemp, Log, TEXT("Waiting For User Control..."));
	
	OnExitTurn();
}

void AJSGameState::OnExitTurn()
{
	UE_LOG(LogTemp, Log, TEXT("Exit Turn..."));

	OnEnterSettleCarat();
}

void AJSGameState::OnEnterSettleCarat()
{
	CheckSynergy();

	UE_LOG(LogTemp, Log, TEXT("Notifying Card Effects..."));

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
	UE_LOG(LogTemp, Log, TEXT("Checking Synergy..."));

}
