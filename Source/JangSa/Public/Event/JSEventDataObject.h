// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JSEventDataObject.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSEventDataObject : public UObject
{
	GENERATED_BODY()

public:
	void InitEventData(class UJSEventData* InEventData);

	TArray<TObjectPtr<UJSEventDataObject>> Events;
};
