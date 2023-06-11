// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JSResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSResultWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void ShowDefeatWidget();
};
