// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JSEventWidget.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSEventWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void InitEventInfoWidget(class UJSEventData* InEventData);

	
};
