// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Data/JSTypes.h"
#include "Data/CardInfoRowBase.h"
#include "JSGameState.generated.h"

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
	AJSGameState();

	virtual void PostInitializeComponents() override;

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

# pragma region Player / Turn Data Section
public:
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
	FORCEINLINE bool AddCurrentCarat(const int32 Value)
	{
		if (GetPlayerData()->CurrentCarat + Value < 0)
		{
			UE_LOG(LogTemp, Log, TEXT("More Money Required"));

			return false;
		}

		GetPlayerData()->CurrentCarat += Value;
		NotifyCurrentCarat.Broadcast(GetPlayerData()->CurrentCarat);
		return true;
	}

	void RefreshPlayerInfo() const;

private:
	TArray<struct FTurnInfoData*> TurnInfoDatas;

	// Data includes Current Carats, Stages and State about Turn
	FPlayerData* PlayerData;
	EGamePlayState GamePlayState;

	UPROPERTY()
	TObjectPtr<class UJSCardFactory> CardActorFactory;
	
	UPROPERTY(VisibleAnywhere, Category="Inventory")
	TArray<TObjectPtr<class AJSCard>> InventoryCards;

	UPROPERTY(VisibleAnywhere, Category="Inventory")
	TArray<TObjectPtr<class AJSCard>> HoldingCards;

	UPROPERTY(VisibleAnywhere, Category="Inventory")
	TArray<TObjectPtr<class AJSCard>> ActivatedCards;
#pragma endregion 

#pragma region Phase Flow Section
	//Phase Flow Section
public:
	// Deprecated
	void DprGameStart();
	void OnResetShop(bool bIsInitTurn = true);

	UFUNCTION(BlueprintCallable)
	void OnExitTurn();

private:
	void SpawnInitCard();

	void OnEnterStartTurn();
	void ShuffleHoldingCards();
	void OnCheckEventQueue();
	void OnEnterSettleCaratPhase();

#pragma endregion 

#pragma region Card Managing / Counting Section
public:
	UFUNCTION(BlueprintCallable)
	TArray<class AJSCard*> CardsInCondition(const FString InRank);

	UFUNCTION(BlueprintCallable)
	int32 CountCardInCardNum(int32 InCardNum);

	UFUNCTION(BlueprintCallable)
	int32 CountCardInCardCharacteristics(FString CardCharacteristics);

	UFUNCTION(BlueprintCallable)
	int32 CountCardInCardRank(FString InCardRank);

	void RegisterActivateCard(class AJSCard* InCard);
	bool PurchaseCard(int32 InCardNum);
	void ArrangeCard();
#pragma endregion 
};
