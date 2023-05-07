// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CardInfoRowBase.h"
#include "JSTypes.h"
#include "JSCard.generated.h"

UCLASS()
class JANGSA_API AJSCard : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AJSCard();

	FCardInfoData GetCardInfo() const;
	void InitCard(const FCardInfoData& InCardData, int32 InObjectID);

protected:
	int CardNum;

	UPROPERTY(VisibleAnywhere, Category=CardInfo)
	FCardInfoData CardData;
	int32 RemainTurn;

	UPROPERTY()
	int32 CardObjID;

	UPROPERTY(VisibleAnywhere, Category=CardRender)
	TObjectPtr<UStaticMeshComponent> KeycapMesh;

	UFUNCTION(BlueprintNativeEvent)
	void OnActivateCardEffect(int32 InOrder);
	UFUNCTION()
	void AddRemainTurn(int32 Value);
	UFUNCTION()
	void OnDestroyCard();
	
};