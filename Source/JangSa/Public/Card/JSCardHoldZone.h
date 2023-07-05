// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "JSCardHoldZone.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API AJSCardHoldZone : public ATriggerBox
{
	GENERATED_BODY()

public:
	AJSCardHoldZone();

	virtual void PostInitializeComponents() override;

private:
	UFUNCTION()
	void OnCardBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnCardEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
