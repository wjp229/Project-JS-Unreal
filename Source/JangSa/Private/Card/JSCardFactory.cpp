// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCardFactory.h"
#include "Card/JSCardEffectComponent.h"
#include "Card/JSCard.h"
#include "Data/JSCardDataAsset.h"
#include "UObject/ConstructorHelpers.h"
#include "Data/JSTypes.h"

UJSCardFactory::UJSCardFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get All Card Data in Data Table

	// Datatable to BlueprintEditable and adjust to class
	// Object Redirector : 
	const ConstructorHelpers::FObjectFinder<UDataTable>
		DT_CardDataInfo(TEXT("/Game/DataTable/DT_CardInfo.DT_CardInfo"));
	if (DT_CardDataInfo.Succeeded())
	{
		DT_CardDataInfo.Object->GetAllRows<FCardInfoData>(TEXT("GetAllRows"), CardInfoDatas);
	}

	// Data Parsing Cards on shop
	for (int32 i = 0; i < CardInfoDatas.Num(); i++)
	{
		CardInfoDatas[i]->Id = i;

		if (CardInfoDatas[i]->ShowOnShop == 1)
		{
			CardInfoDatasOnShop.Add(CardInfoDatas[i]);
		}
	}

	for (int32 i = 0; i < CardInfoDatas.Num(); i++)
	{
		// FText / Text Formatting
		CardInfoDatas[i]->Description.ReplaceInline(TEXT("[Param1]"), *FString::FromInt(CardInfoDatas[i]->Param1));
		CardInfoDatas[i]->Description.ReplaceInline(TEXT("[Param2]"), *FString::FromInt(CardInfoDatas[i]->Param2));
		CardInfoDatas[i]->Description.ReplaceInline(TEXT("[Param3]"), *FString::FromInt(CardInfoDatas[i]->Param3));
	}
	
	// Collect Card Effects
	for (int32 i = 0; i < CardInfoDatas.Num()-1; i++)
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

	//DEPRECATED_JsCard
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
		JSSpawnedCard->InitCard(*CardInfoDatas[CardNum], 0, Cast<UJSCardDataAsset>(CardDataAssets[CardNum]));

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

	return CardInfoDatas[TargetNum];
}

const int32 UJSCardFactory::CheckCardPrice(const int InCardNum)
{
	return CardInfoDatas[InCardNum]->Price;
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
