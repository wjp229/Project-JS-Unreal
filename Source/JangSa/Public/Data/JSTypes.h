#include "JSTypes.generated.h"

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

UENUM()
enum EPlayerControllerState
{
	Selectable,
	Interactable,
	Disabled
};


USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=PlayerData)
	int32 CurrentStage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=PlayerData)
	int32 RemainTurn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=PlayerData)
	int32 PayTurn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=PlayerData)
	int32 CurrentCarat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=PlayerData)
	int32 PayCarat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=PlayerData)
	int32 PurchasedCard;
};

const FString BP_CardEffectPrefixPath = TEXT("/Game/Card/CardEffect/CE_JSCard_");
const FString BP_CardEffectSuffixPath = TEXT(".CE_JSCard_");

const FString DA_CardDataPrefixPath = TEXT("/Game/Card/CardData/DA_JSCard_");
const FString DA_CardDataSuffixPath = TEXT(".DA_JSCard_");