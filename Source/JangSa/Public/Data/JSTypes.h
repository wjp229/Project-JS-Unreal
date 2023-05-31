﻿#include "JSTypes.generated.h"

#pragma once

#define MAX_SLOT_NUM 7

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

UENUM()
enum class ECardState
{
	Inventory,
	Holding,
	Activated,
	Disabled
};

UENUM()
enum class ECardRank
{
	Common,
	Rare,
	Special
};

USTRUCT()
struct FPlayerData
{
	GENERATED_BODY()

	int32 CurrentStage;

	int32 RemainTurn;

	int32 PayTurn;

	int32 CurrentCarat;

	int32 PayCarat;
};

const FString BP_CardEffectPrefixPath = TEXT("/Game/Card/CardEffect/CE_JSCard_");
const FString BP_CardEffectSuffixPath = TEXT(".CE_JSCard_");

const FString DA_CardDataPrefixPath = TEXT("/Game/Card/CardData/DA_JSCard_");
const FString DA_CardDataSuffixPath = TEXT(".DA_JSCard_");