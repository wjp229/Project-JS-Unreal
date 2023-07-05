// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JSEventData.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSEventData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	int32 StageNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	float Probability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	TArray<TSubclassOf<class UJSEventAction>> EventActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	TArray<FString> SelectionParams;
};
