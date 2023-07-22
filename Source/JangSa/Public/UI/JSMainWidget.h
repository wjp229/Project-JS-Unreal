// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JSMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void EnableTurnEndButton();
};
