// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/CardInfoRowBase.h"
#include "JSCardRenderInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJSCardRenderInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JANGSA_API IJSCardRenderInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void UpdateCardInfo(const FCardInfoData InData) = 0;
};
