// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JSTurnEventManager.generated.h"


/**
 * 
 */
UCLASS()
class JANGSA_API AJSTurnEventManager : public AActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnCurrentStageEvents(int32 InStageNum);
	void CallNextEvent();

	void CallEventAction(int32 InStageNum);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Events)
	TArray<TObjectPtr<class UJSEventData>> EventActions;

	// To Activate Action
	TArray<TObjectPtr<class UJSEventAction>> ActionContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Events)
	TArray<TObjectPtr<class UJSEventData>> CurrentStageEvents;
};
