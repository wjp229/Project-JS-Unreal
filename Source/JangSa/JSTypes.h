#include "JSTypes.generated.h"

#pragma once

UENUM()
enum class EGamePhase : uint8
{
	StartPhase = 0,
	ResetShopPhase,
	UserControllPhase,
	ExitPhase,
	SettleCaratPhase
};

UENUM()
enum class ECaratSettlePhase : uint8
{
	CheckSynergy = 0,
	ActivatePositiveEffect,
	ActivateNegativeEffect,
	ActivateSequencialEffect,
	ActivateSequencialChangeEffect,
	ActivateStochasticChangeEffect,
	ReduceCardTurns,
	DestroyCard
};
