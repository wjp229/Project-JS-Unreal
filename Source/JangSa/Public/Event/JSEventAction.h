// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JSEventAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class JANGSA_API UJSEventAction : public UObject
{
	GENERATED_BODY()

public:
	void InitializeEvent();
	
	UFUNCTION(BlueprintNativeEvent)
	void ActivateEvent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=EventParam, meta=(AllowPrivateAccess))
	int32 Param1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=EventParam)
	int32 Param2;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=EventParam)
	int32 Param3;
};
