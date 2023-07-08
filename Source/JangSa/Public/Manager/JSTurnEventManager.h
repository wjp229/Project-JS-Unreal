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

	static AJSTurnEventManager& Get();


	UFUNCTION()
	void SpawnCurrentStageEvents(int32 InStageNum);
	void CallNextEvent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Events)
	TArray<TObjectPtr<class UJSEventData>> EventActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Events)
	TArray<TObjectPtr<class UJSEventData>> CurrentStageEvents;
};
