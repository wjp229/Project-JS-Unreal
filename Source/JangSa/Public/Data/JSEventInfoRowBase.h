// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnInfoRowBase.h"
#include "UObject/NoExportTypes.h"
#include "JSEventInfoRowBase.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSEventInfoRowBase : public UObject
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FJSEventInfoData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	int32 StageNum;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	float Probability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	FString Param1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	FString Param2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EventInfo")
	FString Param3;
};
