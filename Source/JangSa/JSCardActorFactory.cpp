// Fill out your copyright notice in the Description page of Project Settings.


#include "JSCardActorFactory.h"
#include "JSCard.h"
#include "UObject/ConstructorHelpers.h"

UJSCardActorFactory::UJSCardActorFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NewActorClass = AJSCard::StaticClass();

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

	UE_LOG(LogTemp, Log, TEXT("%d CardDataOnShop has made!!"), CardInfoDatasOnShop.Num());
}

void UJSCardActorFactory::SpawnCardActorOnShop()
{
	for (int ix = 0; ix < 4; ix++)
	{
		int32 TargetNum = FMath::RandRange(0, CardInfoDatasOnShop.Num()-1);

		AJSCard* SpawnedCard = Cast<AJSCard>(SpawnCardActor(TargetNum));
	}
}

AActor* UJSCardActorFactory::SpawnCardActor(int CardNum)
{
	AActor* SpawnedCard = SpawnActor(NewActorClass, GetWorld()->GetCurrentLevel(), FTransform(),
	                                 FActorSpawnParameters());
	
	Cast<AJSCard>(SpawnedCard)->InitCard(*CardInfoDatas[CardNum]);

	return SpawnedCard;
}
