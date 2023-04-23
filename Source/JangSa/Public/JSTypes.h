#include "JSTypes.generated.h"

#pragma once

UENUM()
enum class EGameKey
{
	Tap,
	Hold,
	Swipe,
	SwipeTwoPoints,
	Pinch
};

UENUM()
enum class EGamePlayState
{
	Waiting,
	Playing,
	Finished
};

struct FCardData
{
	FString Name;
	FString Rank;
	uint8 bCanControlByUser;
	int32 InitRemainTurn;
	uint8 bShowOnShop;
	int32 Price;
	FString Description;
	int32 Param1;
	int32 Param2;
	int32 Param3;
};

struct FPlayerData
{
	int32 CurrentStage;

	int32 RemainTurn;

	int32 PayTurn;

	int32 CurrentOwnedCarat;

	int32 PayCarat;
};
