// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JSInputInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJSInputInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JANGSA_API IJSInputInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintCallable)
	virtual bool OnSelectActor() = 0;

	virtual void OnReleaseActor() = 0;

	virtual void OnMouseEnterActor() = 0;

	virtual void OnMouseExitActor() = 0;
};
