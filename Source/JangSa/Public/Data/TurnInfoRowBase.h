// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "TurnInfoRowBase.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UTurnInfoRowBase : public UObject
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FTurnInfoData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurnInfo")
	int32 InitPhaseTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurnInfo")
	int32 PayCarat;
};
