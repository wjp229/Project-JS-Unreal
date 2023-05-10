// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "JSTypes.h"
#include "Data/CardInfoRowBase.h"
#include "JSGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivateCardEffect, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddRemainCardTurn, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDestroyCard);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyRemainTurn, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyPayTurn, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyPayCarat, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyCurrentCarat, int32, num);

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
	UPROPERTY(BlueprintAssignable)
	FActivateCardEffect NotifyActivateCardEffect;
	UPROPERTY(BlueprintAssignable)
	FAddRemainCardTurn NotifyAddRemainCardTurn;
	UPROPERTY(BlueprintAssignable)
	FDestroyCard NotifyDestroyCard;
#pragma endregion

	// Delegate로 안해도 될듯
#pragma region NotifyTurnEvent
	UPROPERTY(BlueprintAssignable)
	FNotifyRemainTurn NotifyRemainTurn;
	UPROPERTY(BlueprintAssignable)
	FNotifyPayTurn NotifyPayTurn;
	UPROPERTY(BlueprintAssignable)
	FNotifyPayCarat NotifyPayCarat;
	UPROPERTY(BlueprintAssignable)
	FNotifyCurrentCarat NotifyCurrentCarat;
#pragma endregion

	FORCEINLINE FPlayerData* GetPlayerData() const { return PlayerData; }

	UFUNCTION(BlueprintCallable)
	void SetRemainTurn(const int32 InRemainTurn);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void AddRemainTurn(const int32 Value)
	{
		SetRemainTurn(GetPlayerData()->RemainTurn + Value);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPayTurn(const int32 InPayTurn)
	{
		GetPlayerData()->PayTurn = InPayTurn;
		NotifyPayTurn.Broadcast(InPayTurn);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPayCarat(const int32 InPayCarat)
	{
		GetPlayerData()->PayCarat = InPayCarat;
		NotifyPayCarat.Broadcast(InPayCarat);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void AddCurrentCarat(const int32 Value)
	{
		GetPlayerData()->CurrentCarat += Value;
		NotifyCurrentCarat.Broadcast(GetPlayerData()->CurrentCarat);
	}

	// Deprecated
	void DprGameStart();
	void SetNextPhase();

	bool PurchaseCard(int32 InCardNum);
	void OnResetShop(bool bIsInitTurn = true);
	void RefreshPlayerInfo() const;

	UFUNCTION(BlueprintCallable)
	void OnExitTurn();

private:
	// Data includes Current Carats, Stages and State about Turn
	FPlayerData* PlayerData;
	EGamePlayState GamePlayState;

	UPROPERTY()
	TArray<TObjectPtr<class AJSCard>> HoldingCards;

	UPROPERTY()
	TArray<TObjectPtr<AJSCard>> ActivatedCards;
	
	UPROPERTY()
	TObjectPtr<class UJSCardFactory> CardActorFactory;
	
	// DataTable About Turn
	TArray<struct FTurnInfoData*> TurnInfoDatas;

	void OnCheckEventQueue();
	void OnEnterStartTurn();

	// Activate each card's effect, reduce turn, and destory when card's remain turn is zero
	void OnEnterSettleCarat();

public:
};
