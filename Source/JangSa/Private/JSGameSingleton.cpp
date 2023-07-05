// Fill out your copyright notice in the Description page of Project Settings.


#include "JSGameSingleton.h"
#include "UObject/ConstructorHelpers.h"

UJSGameSingleton::UJSGameSingleton()
{
	// Turn Info Parser
	const ConstructorHelpers::FObjectFinder<UDataTable> DT_TurnDataTableRef(
		TEXT("/Game/DataTable/DT_TurnInfo.DT_TurnInfo"));
	if (DT_TurnDataTableRef.Succeeded())
	{
		const UDataTable* DataTable = DT_TurnDataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, TurnInfoDatas,
			[](uint8* Value)
			{
				return *reinterpret_cast<FTurnInfoData*>(Value);
			}
		);
	}

	// Card Info Parser
	const ConstructorHelpers::FObjectFinder<UDataTable>
		DT_CardDataInfo(TEXT("/Game/DataTable/DT_CardInfo.DT_CardInfo"));
	if (DT_CardDataInfo.Succeeded())
	{
		DT_CardDataInfo.Object->GetAllRows<FCardInfoData>(TEXT("GetAllRows"), CardInfoDatas);
	}
	for (int32 i = 0; i < CardInfoDatas.Num(); i++)
	{
		// FText / Text Formatting
		CardInfoDatas[i]->Description.ReplaceInline(TEXT("[Param1]"), *FString::FromInt(CardInfoDatas[i]->Param1));
		CardInfoDatas[i]->Description.ReplaceInline(TEXT("[Param2]"), *FString::FromInt(CardInfoDatas[i]->Param2));
		CardInfoDatas[i]->Description.ReplaceInline(TEXT("[Param3]"), *FString::FromInt(CardInfoDatas[i]->Param3));
	}
	

	// Start Card Info Parser
	const ConstructorHelpers::FObjectFinder<UDataTable> DT_StartCardInfoTableRef(
		TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_StartCardInfo.DT_StartCardInfo'"));
	if (DT_StartCardInfoTableRef.Succeeded())
	{
		DT_StartCardInfoTableRef.Object->GetAllRows<FStartCardInfoData>(TEXT("GetAllRows"), StartCardInfoDatas);
	}

	// Event Info Parser
	const ConstructorHelpers::FObjectFinder<UDataTable> DT_EventInfoTableRef(
		TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_EventInfo.DT_EventInfo'"));
	if (DT_EventInfoTableRef.Succeeded())
	{
		DT_EventInfoTableRef.Object->GetAllRows<FJSEventInfoData>(TEXT("GetAllRows"), EventInfoDatas);
	}
}

UJSGameSingleton& UJSGameSingleton::Get()
{
	UJSGameSingleton* Singleton = CastChecked<UJSGameSingleton>(GEngine->GameSingleton);

	if(Singleton)
	{
		return *Singleton;
	}

	return *NewObject<UJSGameSingleton>();
}
