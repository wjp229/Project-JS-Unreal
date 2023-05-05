// Fill out your copyright notice in the Description page of Project Settings.


#include "JSCardFactory.h"
#include "Card/JSCard.h"
#include "UObject/ConstructorHelpers.h"

UJSCardFactory::UJSCardFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	const ConstructorHelpers::FObjectFinder<UDataTable>
		DT_CardDataInfo(TEXT("/Game/DataTable/DT_CardInfo.DT_CardInfo"));
	if (DT_CardDataInfo.Succeeded())
	{
		DT_CardDataInfo.Object->GetAllRows<FCardInfoData>(TEXT("GetAllRows"), CardInfoDatas);
	}
	
	for (int i = 0; i < CardInfoDatas.Num(); i++)
	{

		if (CardInfoDatas[i]->ShowOnShop == 1)
		{
			CardInfoDatasOnShop.Add(CardInfoDatas[i]);
		}
	}
}

TArray<FCardInfoData*>& UJSCardFactory::SpawnCardActorOnShop()
{
	TempCardInfoDatas.Empty();
	
	for (int ix = 0; ix < 4; ix++)
	{
		int32 TargetNum = FMath::RandRange(0, CardInfoDatasOnShop.Num()-1);
		
		// UJSCard* NewCard = Cast<UJSCard>(SpawnCardActor(TargetNum));

		FCardInfoData* InCardInfoData(SpawnCardData(TargetNum));
		
		TempCardInfoDatas.Emplace(InCardInfoData);
	}

	return TempCardInfoDatas;
}

UObject* UJSCardFactory::SpawnCardActor(int CardNum)
{
	UObject* SpawnedCard = NewObject<UJSCard>(GetWorld(), UJSCard::StaticClass());
	
	Cast<UJSCard>(SpawnedCard)->InitCard(*CardInfoDatas[CardNum], 0);

	return SpawnedCard;
}

FCardInfoData* UJSCardFactory::SpawnCardData(int CardNum, bool IsRandom)
{
	int32 TargetNum = CardNum;
	if(IsRandom)
	{
		TargetNum = FMath::RandRange(0, CardInfoDatasOnShop.Num()-1);
	}

	return CardInfoDatas[TargetNum];
}