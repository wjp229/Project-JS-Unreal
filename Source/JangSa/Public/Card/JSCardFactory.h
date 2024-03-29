// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Card/JSCard.h"
#include "Data/CardInfoRowBase.h"
#include "UObject/NoExportTypes.h"
#include "JSCardFactory.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class JANGSA_API UJSCardFactory : public UObject
{
	GENERATED_BODY()

public:
	UJSCardFactory(const FObjectInitializer& ObjectInitializer);

	void InitFactory();

	TArray<struct FCardInfoData*>& UJSCardFactory::SpawnCardActorOnShop();
	
	AActor* SpawnCardActor(int CardNum, FVector const* InLocation = 0);
	
	FCardInfoData* SpawnCardData(int CardNum, bool IsRandom = false);

	const int32 CheckCardPrice(const int CardNum);

private:
	TArray<FCardInfoData*> CardInfoDatasOnShop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CardData, meta=(AllowPrivateAccess))
	TArray<TObjectPtr<class UJSCardDataAsset>> CardDataAssets;

	TArray<FCardInfoData*> TempCardInfoDatas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CardData, meta=(AllowPrivateAccess))
	TSubclassOf<class AJSCard> CardBP;

	// Object Pooling
private:
	void CreateCardObjectsInPool();
	AActor* GetPooledObject();

	TArray<TObjectPtr<AActor>> Pool;
public:
	void ReturnObject(AActor* InReturnObj);

};
