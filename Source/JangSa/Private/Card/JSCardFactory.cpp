// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCardFactory.h"

#include "JSGameSingleton.h"
#include "Card/JSCardEffectComponent.h"
#include "Card/JSCard.h"
#include "Data/JSCardDataAsset.h"
#include "UObject/ConstructorHelpers.h"
#include "Data/JSTypes.h"

UJSCardFactory::UJSCardFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Collect Card Effects
	for (int32 i = 0; i < 15; i++)
	{
		FString PreTargetAddress = DA_CardDataPrefixPath;
		FString ProTargetAddress = DA_CardDataSuffixPath;

		FString TargetAddress;
		TargetAddress.Append(PreTargetAddress);
		TargetAddress.Append(FString::FromInt(i));
		TargetAddress.Append(ProTargetAddress);
		TargetAddress.Append(FString::FromInt(i));

		const ConstructorHelpers::FObjectFinder<UJSCardDataAsset> CardDataRef(*TargetAddress);
		if (nullptr != CardDataRef.Object)
		{
			UJSCardDataAsset* Data = CardDataRef.Object;

			if (nullptr != Data)
			{
				CardDataAssets.Emplace(Data);
			}
		}
	}
	
	// 
	static ConstructorHelpers::FClassFinder<AJSCard> JsCardRef(TEXT("/Game/Card/BP_JSCard.BP_JSCard_C"));
	if(JsCardRef.Succeeded())
	{
		CardBP = JsCardRef.Class;
	}
}

void UJSCardFactory::InitFactory()
{
	// Data Parsing Cards on shop
	for (int32 i = 0; i < UJSGameSingleton::Get().GetMaxCardInfoCount(); i++)
	{
		if (UJSGameSingleton::Get().GetCardInfo(i)->ShowOnShop == 1)
		{
			CardInfoDatasOnShop.Add(UJSGameSingleton::Get().GetCardInfo(i));
		}
	}
}

TArray<FCardInfoData*>& UJSCardFactory::SpawnCardActorOnShop()
{
	TempCardInfoDatas.Empty();

	for (int ix = 0; ix < 4; ix++)
	{
		int32 TargetNum = FMath::RandRange(0, CardInfoDatasOnShop.Num() - 1);

		FCardInfoData* InCardInfoData(SpawnCardData(TargetNum));

		TempCardInfoDatas.Emplace(InCardInfoData);
	}

	return TempCardInfoDatas;
}

// To do : Actor Pooling
AActor* UJSCardFactory::SpawnCardActor(int CardNum, FVector const* InLocation)
{
	if(Pool.Num() == 0)
	{
		CreateCardObjectsInPool();
	}
	
	if(CardNum >= CardDataAssets.Num()) return nullptr;
	
	AActor* SpawnedCard = GetPooledObject();
	SpawnedCard->SetActorLocation(*InLocation);
	

	AJSCard* JSSpawnedCard = Cast<AJSCard>(SpawnedCard);

	if (nullptr != JSSpawnedCard)
	{
		JSSpawnedCard->InitCard(*UJSGameSingleton::Get().GetCardInfo(CardNum), 0, Cast<UJSCardDataAsset>(CardDataAssets[CardNum]));

		return SpawnedCard;
	}

	return nullptr;
}

FCardInfoData* UJSCardFactory::SpawnCardData(int CardNum, bool IsRandom)
{
	int32 TargetNum = CardNum;
	if (IsRandom)
	{
		TargetNum = FMath::RandRange(0, CardInfoDatasOnShop.Num() - 1);
	}

	return UJSGameSingleton::Get().GetCardInfo(TargetNum);
}

const int32 UJSCardFactory::CheckCardPrice(const int InCardNum)
{
	return UJSGameSingleton::Get().GetCardInfo(InCardNum)->Price;
}

void UJSCardFactory::CreateCardObjectsInPool()
{
	for(int i = 0; i < 50; i++)
	{
		AActor* PoolObj = GetWorld()->SpawnActor(CardBP);
		
		Pool.Emplace(PoolObj);

		PoolObj->SetActorHiddenInGame(true);
	}
}

AActor* UJSCardFactory::GetPooledObject()
{
	if(Pool.Num() <= 0 ) return nullptr;
	
	AActor* ReturnObj = Pool.Pop();

	ReturnObj->SetActorHiddenInGame(false);
	
	return ReturnObj;
}

void UJSCardFactory::ReturnObject(AActor* InReturnObj)
{
	Pool.Emplace(InReturnObj);

	InReturnObj->SetActorHiddenInGame(true);
}
