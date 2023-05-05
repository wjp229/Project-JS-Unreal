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

UENUM()
enum class ECardRenderState
{
	UMG,
	Paper,
	Stone
};

struct FPlayerData
{
	int32 CurrentStage;

	int32 RemainTurn;

	int32 PayTurn;

	int32 CurrentOwnedCarat;

	int32 PayCarat;
};
