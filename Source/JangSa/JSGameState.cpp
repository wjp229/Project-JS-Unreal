// Fill out your copyright notice in the Description page of Project Settings.


#include "JSGameState.h"
#include "TurnInfoRowBase.h"
#include "Engine/DataTable.h"

AJSGameState::AJSGameState()
{
	CurrentStage = 0;
	
	const ConstructorHelpers::FObjectFinder<UDataTable> TurnDataTable(TEXT("/Game/DataTable/DT_TurnInfo.DT_TurnInfo"));

	if(TurnDataTable.Succeeded())
	{
		TurnDataTable.Object->GetAllRows<FTurnInfoData>(TEXT("GetAllRows"), TurnInfoDatas);
	}

	SetPayTurn(TurnInfoDatas[CurrentStage]->InitPhaseTurn);
	SetRemainTurn(PayTurn);

	PayCarat = TurnInfoDatas[CurrentStage]->PayCarat;
}

void AJSGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UE_LOG(LogTemp, Log, TEXT("Remain Turn : %d // Remain Carat : %d"), RemainTurn, PayCarat);
}

void AJSGameState::OnCheckEventQueue()
{
}

void AJSGameState::OnEnterStartTurn()
{
	GamePhase = EGamePhase::StartPhase;

	if(RemainTurn == 0)
	{
		// Pay Carat Or Game Over

		// if Payed
		// if(true)
		// {
		// 	CurrentStage++;
		// 	SetPayTurn(TurnInfoDatas[CurrentStage]->InitPhaseTurn);
		// 	SetRemainTurn(PayTurn);
		// 	SetPayCarat(TurnInfoDatas[CurrentStage]->PayCarat);
		// }
		// else
		// {
		// 	// Can't Pay Carat
		// }
	}

	OnResetShop();
}

void AJSGameState::OnResetShop()
{
	GamePhase = EGamePhase::ResetShopPhase;

	// Reset Shop

	OnEnterUserControlTurn();
}

void AJSGameState::OnEnterUserControlTurn()
{
	GamePhase = EGamePhase::UserControllPhase;

	// Keep phase state until TurnEnd button clicked
}

void AJSGameState::OnExitTurn()
{
	GamePhase = EGamePhase::ExitPhase;

	AddRemainTurn(-1);
	
	OnEnterSettleCarat();
}

void AJSGameState::OnEnterSettleCarat()
{
	GamePhase = EGamePhase::SettleCaratPhase;
	
	CheckSynergy();
	
	// Activate Each Card Effects
	NotifyPositiveCardEffect.Broadcast(0);
	NotifyNegativeCardEffect.Broadcast(0);
	NotifySequencialCardEffect.Broadcast(0);

	// Activate Each Card's Change Effects
	NotifySequencialCardChange.Broadcast(0);
	NotifyStochasticCardChange.Broadcast(0);

	// Reduce Card Turns
	NotifyAddRemainCardTurn.Broadcast(-1);

	// If Each Card's remain turn come to zero, Destroy
	NotifyDestroyCard.Broadcast();

	OnEnterStartTurn();
}

void AJSGameState::CheckSynergy()
{
	
}