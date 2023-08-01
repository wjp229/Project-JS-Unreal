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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyResultCarat, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyCheckEvent, int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyPlayerControllerState, EPlayerControllerState, state);

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
	UPROPERTY(BlueprintAssignable)
	FNotifyResultCarat NotifyResultCarat;

	FNotifyCheckEvent NotifyCheckEvent;
	FNotifyPlayerControllerState NotifyPlayerControllerState;
#pragma endregion

#pragma region Player / Turn Data Section
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

	FORCEINLINE void AddTurnResultCarat(const int32 InValue)
	{
		TurnResultCarat += InValue;
		NotifyResultCarat.Broadcast(TurnResultCarat);
	}

	void RefreshPlayerInfo() const;

private:
	// Data includes Current Carats, Stages and State about Turn
	FPlayerData* PlayerData;
	EGamePlayState GamePlayState;

	UPROPERTY()
	TObjectPtr<class UJSCardFactory> CardActorFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CardFactory, meta=(AllowPrivateAccess))
	TSubclassOf<class UJSCardFactory> CardFactoryRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Slot, meta=(AllowPrivateAccess))
	TSubclassOf<class AJSCardSlot> CardSlot;

	UPROPERTY(VisibleAnywhere, Category="Slot")
	TArray<TObjectPtr<AJSCardSlot>> CardSlots;
	
	UPROPERTY(VisibleAnywhere, Category="Inventory")
	TArray<TObjectPtr<class AJSCard>> InventoryCards;

	UPROPERTY(VisibleAnywhere, Category="Inventory")
	TArray<TObjectPtr<class AJSCard>> HoldingCards;

	UPROPERTY(VisibleAnywhere, Category="Inventory")
	TArray<TObjectPtr<class AJSCard>> ActivatedCards;

	UPROPERTY(VisibleAnywhere, Category="TurnResult")
	int32 TurnResultCarat;

#pragma endregion 

#pragma region Phase Flow Section
	//Phase Flow Section
public:
	// Deprecated
	void DprGameStart();
	void OnEnterStartTurn();
	void OnResetShop(bool bIsInitTurn = true);
	void FoldShop(bool bIsFolded);
	void ExitShop();

	UFUNCTION(BlueprintCallable)
	void OnExitTurn();

private:
	uint8 bCanReroll : 1;

private:
	void SpawnInitCard();

	void ShuffleHoldingCards();
	void OnCheckEventQueue();
	void OnEnterSettleCaratPhase();

	FTimerHandle ActivateHandler;

#pragma endregion 

#pragma region Card Managing / Counting Section
public:
	UFUNCTION(BlueprintCallable)
	TArray<class AJSCard*> CardsInCondition(const FString InRank);

	UFUNCTION(BlueprintCallable)
	int32 CountCardInCardNum(int32 InCardNum);

	UFUNCTION(BlueprintCallable)
	int32 CountCardInCardCharacteristics(FString InCharacteristics);

	UFUNCTION(BlueprintCallable)
	int32 CountCardInCardRank(FString InCardRank);

	bool RegisterActivateCard(class AJSCard* InCard, int32 SlotNum, FVector& SlotPosition);
	bool UnregisterActivateCard(class AJSCard* InCard);
	bool PurchaseCard(int32 InCardNum);
	void ArrangeCard();
#pragma endregion
public:
	class AJSTurnEventManager* GetTurnManager() const;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=EventManager, meta=(AllowPrivateAccess))
	TObjectPtr<class AJSTurnEventManager> TurnManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=EventManager, meta=(AllowPrivateAccess))
	TSubclassOf<class AJSTurnEventManager> TurnManagerClass;
};
