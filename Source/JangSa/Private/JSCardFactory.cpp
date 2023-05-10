// Fill out your copyright notice in the Description page of Project Settings.


#include "JSCardFactory.h"
#include "JSCardEffectComponent.h"
#include "Card/JSCard.h"
#include "UnrealEd/Private/Toolkits/SStandaloneAssetEditorToolkitHost.h"
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
	
	for (int32 i = 0; i < CardInfoDatas.Num(); i++)
	{
		CardInfoDatas[i]->Id = i;
		
		if (CardInfoDatas[i]->ShowOnShop == 1)
		{
			CardInfoDatasOnShop.Add(CardInfoDatas[i]);
		}
	}

	for(int32 i = 0; i < 2/*CardInfoDatas.Num()*/; i++)
	{
		FString PreTargetAddress = TEXT("/Game/Card/CE_JSCard_");
		FString ProTargetAddress = TEXT(".CE_JSCard_");

		FString TargetAddress;
		TargetAddress.Append(PreTargetAddress);
		TargetAddress.Append(FString::FromInt(i));
		TargetAddress.Append(ProTargetAddress);
		TargetAddress.Append(FString::FromInt(i));
		TargetAddress.Append(TEXT("_C"));

		const ConstructorHelpers::FClassFinder<UJSCardEffectComponent> CardEffectRef(*TargetAddress);
		if(nullptr != CardEffectRef.Class)
		{
			UE_LOG(LogTemp, Log, TEXT("Load Succeed!!"));

			TSubclassOf<UJSCardEffectComponent> Effect = CardEffectRef.Class;
			
			if(nullptr != Effect)
			{
				EffectComponents.Emplace(Effect);

				UE_LOG(LogTemp, Log, TEXT("Casting Succeed!!"));
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Casting Failed!!"));

			}
		}
	}
}

TArray<FCardInfoData*>& UJSCardFactory::SpawnCardActorOnShop()
{
	TempCardInfoDatas.Empty();
	
	for (int ix = 0; ix < 4; ix++)
	{
		int32 TargetNum = FMath::RandRange(0, CardInfoDatasOnShop.Num()-1);
		
		FCardInfoData* InCardInfoData(SpawnCardData(TargetNum));
		
		TempCardInfoDatas.Emplace(InCardInfoData);
	}

	return TempCardInfoDatas;
}

AActor* UJSCardFactory::SpawnCardActor(int CardNum, FVector const* InLocation)
{
	AActor* SpawnedCard = GetWorld()->SpawnActor(AJSCard::StaticClass(), InLocation);
	AJSCard* JSSpawnedCard = Cast<AJSCard>(SpawnedCard);
	
	if(nullptr != JSSpawnedCard)// || CardNum > EffectComponents.Num())
	{
		UE_LOG(LogTemp, Log, TEXT("%d"), EffectComponents.Num());
		UJSCardEffectComponent* EffectComponent = NewObject<UJSCardEffectComponent>(JSSpawnedCard, EffectComponents[0]);
		
		JSSpawnedCard->InitCard(*CardInfoDatas[CardNum], 0, EffectComponent);
	}
	
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

const int32 UJSCardFactory::CheckCardPrice(const int InCardNum) 
{
	return CardInfoDatas[InCardNum]->Price;
}
