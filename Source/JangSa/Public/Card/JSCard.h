// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JSGameState.h"
#include "Data/CardInfoRowBase.h"
#include "GameFramework/Actor.h"
#include "JSCard.generated.h"

UCLASS()
class JANGSA_API UJSCard : public UObject
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	UJSCard();

	FCardInfoData GetCardInfo() const;
	void InitCard(const FCardInfoData& InCardData, AJSGameState* GameState, int32 InObjectID);

protected:
	int CardNum;

	UPROPERTY()
	FCardInfoData CardData;
	int32 RemainTurn;

	UPROPERTY()
	int32 CardObjID;

	UFUNCTION()
	void OnActivateCardEffect(int32 InOrder);
	UFUNCTION()
	void AddRemainTurn(int32 Value);
	UFUNCTION()
	void OnDestroyCard();
	
};