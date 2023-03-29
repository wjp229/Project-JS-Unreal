// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnInfoRowBase.h"
#include "UObject/NoExportTypes.h"
#include "CardInfoRowBase.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UCardInfoRowBase : public UObject
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FCardInfoData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	FString Rank;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	uint8 CanControlByUser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	int32 InitRemainTurn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	uint8 ShowOnShop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	int32 Probability;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	FString Description;

};
