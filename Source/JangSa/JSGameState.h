// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "JSTypes.h"
#include "JSGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivatePositiveCard, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivateNegativeCard, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivateNeutralCard, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivateSequencialCardChange, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivateStochasticCardChange, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddRemainCardTurn, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDestroyCard);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyRemainTurn, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyPayTurn, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyPayCarat, int32, num);
/**
 * 
 */
UCLASS()
class JANGSA_API AJSGameState : public AGameState
{
	GENERATED_BODY()

public:
	AJSGameState();

#pragma region SettleCaratDelegate
	// Process in Activating Turn
	FActivatePositiveCard NotifyPositiveCardEffect;
	FActivateNegativeCard NotifyNegativeCardEffect;
	FActivateNeutralCard NotifySequencialCardEffect;
	FActivateSequencialCardChange NotifySequencialCardChange;
	FActivateStochasticCardChange NotifyStochasticCardChange;
	FAddRemainCardTurn NotifyAddRemainCardTurn;
	FDestroyCard NotifyDestroyCard;
#pragma endregion 
	
	FNotifyRemainTurn NotifyRemainTurn;
	FNotifyPayTurn NotifyPayTurn;
	FNotifyPayCarat NotifyPayCarat;
	
	FORCEINLINE void SetRemainTurn(const int32 InRemainTurn) { RemainTurn = InRemainTurn; NotifyRemainTurn.Broadcast(RemainTurn); }
	FORCEINLINE void AddRemainTurn(const int32 Value) { SetRemainTurn(RemainTurn + Value); }
	FORCEINLINE void SetPayTurn(const int32 InPayTurn) { PayTurn = InPayTurn; NotifyRemainTurn.Broadcast(RemainTurn); }

	FORCEINLINE void SetPayCarat(const int32 InPayCarat) { PayCarat = InPayCarat; NotifyPayCarat.Broadcast(PayCarat); }
	
	virtual void PostInitializeComponents() override;
	
private:
	EGamePhase GamePhase;
	ECaratSettlePhase CaratSettlePhase;

	int32 CurrentStage;
	int32 RemainTurn;
	int32 PayTurn;
	int32 PayCarat;
	
	TArray<struct FTurnInfoData*> TurnInfoDatas;

	
	void OnCheckEventQueue();

	// 
	void OnEnterStartTurn();

	//
	void OnResetShop();

	//
	void OnEnterUserControlTurn();

	// Activate each card's effect, reduce turn, and destory when card's remain turn is zero
	void OnEnterSettleCarat();
	void CheckSynergy();

	//
	void OnExitTurn();
};