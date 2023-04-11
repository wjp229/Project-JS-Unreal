// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	const FCardData* GetCardInfo() const;
	void InitCard(FCardData* InCardData);

protected:
	FCardData* CardData;

	int RemainTurn;

	void OnActivateCardEffect(int InOrder);
	void AddRemainTurn(int Value);
	void OnDestroyCard();
	
public:
	// Called every frame
	virtual void PostInitializeComponents() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
