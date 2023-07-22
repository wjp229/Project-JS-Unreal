// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CardInfoRowBase.h"
#include "Data/JSEventInfoRowBase.h"
#include "Data/StartCardInfoRowBase.h"
#include "Data/TurnInfoRowBase.h"
#include "JSGameSingleton.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class JANGSA_API UJSGameSingleton : public UObject
{
	GENERATED_BODY()

public:
	UJSGameSingleton();

	static UJSGameSingleton& Get();

	FORCEINLINE FTurnInfoData GetTurnInfo(int32 InTurn)
	{
		return TurnInfoDatas.IsValidIndex(InTurn) ? TurnInfoDatas[InTurn] : FTurnInfoData();
	}
	FORCEINLINE int32 GetMaxTurnCount() const
	{
		return TurnInfoDatas.Num();
	}

	FORCEINLINE FCardInfoData* GetCardInfo(int32 InCardNum)
	{
		return CardInfoDatas[InCardNum];//CardInfoDatas.IsValidIndex(InCardNum) ? CardInfoDatas[InCardNum] : FCardInfoData();
	}
	FORCEINLINE int32 GetMaxCardInfoCount() const
	{
		return CardInfoDatas.Num();
	}

	FORCEINLINE TArray<FStartCardInfoData*> GetStartCardInfos()
	{
		return StartCardInfoDatas;
	}

	FORCEINLINE TArray<FJSEventInfoData*> GetEventInfos()
	{
		return EventInfoDatas;
	}

private:
	TArray<FTurnInfoData> TurnInfoDatas;
	TArray<FCardInfoData*> CardInfoDatas;
	TArray<FStartCardInfoData*> StartCardInfoDatas;

	TArray<FJSEventInfoData*> EventInfoDatas;
};
