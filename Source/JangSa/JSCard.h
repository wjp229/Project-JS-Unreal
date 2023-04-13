// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardInfoRowBase.h"
#include "JSTypes.h"
#include "GameFramework/Actor.h"
#include "JSCard.generated.h"

UCLASS()
class JANGSA_API AJSCard : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AJSCard();

	FCardInfoData GetCardInfo() const;
	void InitCard(const FCardInfoData& InCardData);

protected:
	int CardNum;

	UPROPERTY()
	FCardInfoData CardData;
	int RemainTurn;

	UPROPERTY()
	UStaticMeshComponent* CardMesh;

	UFUNCTION()
	void OnActivateCardEffect(int InOrder);
	UFUNCTION()
	void AddRemainTurn(int Value);
	UFUNCTION()
	void OnDestroyCard();
	
public:
	// Called every frame
	virtual void PostInitializeComponents() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
