// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCardFactory.h"
#include "Card/JSCardEffectComponent.h"
#include "Card/JSCard.h"
#include "UObject/ConstructorHelpers.h"
#include "Data/JSTypes.h"

UJSCardFactory::UJSCardFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get All Card Data in Data Table
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

	// Collect Card Effects
	for (int32 i = 0; i < CardInfoDatas.Num()-1; i++)
	{
		FString PreTargetAddress = BP_CardEffectPrefixPath;
		FString ProTargetAddress = BP_CardEffectSuffixPath;

		FString TargetAddress;
		TargetAddress.Append(PreTargetAddress);
		TargetAddress.Append(FString::FromInt(i));
		TargetAddress.Append(ProTargetAddress);
		TargetAddress.Append(FString::FromInt(i));
		TargetAddress.Append(TEXT("_C"));

		const ConstructorHelpers::FClassFinder<UJSCardEffectComponent> CardEffectRef(*TargetAddress);
		if (nullptr != CardEffectRef.Class)
		{
			TSubclassOf<UJSCardEffectComponent> Effect = CardEffectRef.Class;

			if (nullptr != Effect)
			{
				EffectComponents.Emplace(Effect);
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

AActor* UJSCardFactory::SpawnCardActor(int CardNum, FVector const* InLocation)
{
	if(CardNum >= EffectComponents.Num()) return nullptr;
	
	AActor* SpawnedCard = GetWorld()->SpawnActor(CardBP, InLocation);
	AJSCard* JSSpawnedCard = Cast<AJSCard>(SpawnedCard);

	if (nullptr != JSSpawnedCard)
	{
		UJSCardEffectComponent* EffectComponent = NewObject<UJSCardEffectComponent>(
			JSSpawnedCard, EffectComponents[CardNum]);

		JSSpawnedCard->InitCard(*CardInfoDatas[CardNum], 0, EffectComponent);
		
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
