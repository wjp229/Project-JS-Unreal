// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JSCardFactory.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSCardFactory : public UObject
{
	GENERATED_BODY()

public:
	UJSCardFactory(const FObjectInitializer& ObjectInitializer);

	TArray<class UJSCard> SpawnCardActorOnShop();

	UFUNCTION()
	UObject* SpawnCardActor(int CardNum);

private:
	TArray<struct FCardInfoData*> CardInfoDatas;
	TArray<FCardInfoData*> CardInfoDatasOnShop;
};
