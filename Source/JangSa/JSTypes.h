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
	int32 Probability;
	FString Description;
};

struct FPlayerData
{
	int32 CurrentStage;

	int32 RemainTurn;

	int32 PayTurn;

	int32 CurrentOwnedCarat;

	int32 PayCarat;
};
