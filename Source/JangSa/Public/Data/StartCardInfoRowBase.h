// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnInfoRowBase.h"
#include "UObject/NoExportTypes.h"
#include "StartCardInfoRowBase.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UStartCardInfoRowBase : public UObject
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FStartCardInfoData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StartCardInfo")
	int32 StageNum;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StartCardInfo")
	int32 FieldNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StartCardInfo")
	int32 Id;
};
