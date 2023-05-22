// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JSControlData.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSControlData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UJSControlData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category=Camera)
	FVector CameraLocation;
};
