// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CardInfoRowBase.h"
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

	TArray<struct FCardInfoData*>& UJSCardFactory::SpawnCardActorOnShop();
	
	AActor* SpawnCardActor(int CardNum, FVector const* InLocation = 0);
	
	FCardInfoData* SpawnCardData(int CardNum, bool IsRandom = false);

	const int32 CheckCardPrice(const int CardNum);

private:
	TArray<FCardInfoData*> CardInfoDatas;
	TArray<FCardInfoData*> CardInfoDatasOnShop;

	TArray<FCardInfoData*> TempCardInfoDatas;
};
