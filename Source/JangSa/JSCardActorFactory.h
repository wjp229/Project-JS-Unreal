// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorFactories/ActorFactory.h"
#include "JSCardActorFactory.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSCardActorFactory : public UActorFactory
{
	GENERATED_BODY()

public:
	UJSCardActorFactory(const FObjectInitializer& ObjectInitializer);

	void SpawnCardActorOnShop();

	UFUNCTION()
	AActor* SpawnCardActor(int CardNum);

private:
	TArray<struct FCardInfoData*> CardInfoDatas;
	TArray<struct FCardInfoData*> CardInfoDatasOnShop;
};
