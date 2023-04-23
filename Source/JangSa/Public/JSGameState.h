// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "JSTypes.h"
#include "JSGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivateCardEffect, int32, num);
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
	virtual void PostInitializeComponents() override;

private:
public:
	AJSGameState();

#pragma region SettleCaratDelegate
	// Process in Activating Turn
	FActivateCardEffect NotifyActivateCardEffect;
	FAddRemainCardTurn NotifyAddRemainCardTurn;
	FDestroyCard NotifyDestroyCard;
#pragma endregion

	// Delegate로 안해도 될듯
#pragma region NotifyTurnEvent
	FNotifyRemainTurn NotifyRemainTurn;
	FNotifyPayTurn NotifyPayTurn;
	FNotifyPayCarat NotifyPayCarat;
#pragma endregion

	FORCEINLINE FPlayerData* GetPlayerData() const { return PlayerData; }

	void SetRemainTurn(const int32 InRemainTurn);
	FORCEINLINE void AddRemainTurn(const int32 Value) { SetRemainTurn(GetPlayerData()->RemainTurn + Value); }
	FORCEINLINE void SetPayTurn(const int32 InPayTurn)
	{
		GetPlayerData()->PayTurn = InPayTurn;
		NotifyRemainTurn.Broadcast(InPayTurn);
	}

	FORCEINLINE void SetPayCarat(const int32 InPayCarat)
	{
		GetPlayerData()->PayCarat = InPayCarat;
		NotifyPayCarat.Broadcast(InPayCarat);
	}

	// Deprecated
	void SetNextTurn();
	void SetNextPhase();

private:
	// Data includes Current Carats, Stages and State about Turn
	FPlayerData* PlayerData;

	EGamePlayState GamePlayState;

	UPROPERTY()
	TObjectPtr<class UJSCardFactory> CardActorFactory;

	UPROPERTY()
	TObjectPtr<class UJSRenderManager> RenderManager;
	
	// DataTable About Turn
	TArray<struct FTurnInfoData*> TurnInfoDatas;

	void OnCheckEventQueue();
	void CheckSynergy();
	void OnEnterStartTurn();
	void OnResetShop();
	void OnEnterUserControlTurn();

	// Activate each card's effect, reduce turn, and destory when card's remain turn is zero
	void OnEnterSettleCarat();
	void OnExitTurn();

public:
};
