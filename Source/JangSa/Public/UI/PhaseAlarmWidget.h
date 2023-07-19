// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PhaseAlarmWidget.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UPhaseAlarmWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void SetPhaseText(const FString& InText);
};
