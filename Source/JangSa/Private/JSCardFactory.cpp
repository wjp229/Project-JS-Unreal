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

void UJSCardFactory::SpawnCardActorOnShop()
{
	for (int ix = 0; ix < 4; ix++)
	{
		int32 TargetNum = FMath::RandRange(0, CardInfoDatasOnShop.Num()-1);

		Cast<UJSCard>(SpawnCardActor(TargetNum));
	}
}

UObject* UJSCardFactory::SpawnCardActor(int CardNum)
{
	UObject* SpawnedCard = NewObject<UJSCard>(GetWorld(), UJSCard::StaticClass());
	
	Cast<UJSCard>(SpawnedCard)->InitCard(*CardInfoDatas[CardNum], Cast<AJSGameState>(GetWorld()->GetGameState()), 0);

	return SpawnedCard;
}
