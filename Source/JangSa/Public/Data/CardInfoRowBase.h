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
	int32 Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	FString Rank;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	uint8 CanControlByUser : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	int32 InitRemainTurn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	uint8 ShowOnShop : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	int32 Price;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	FString Characteristic1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	FString Characteristic2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	int32 Param1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	int32 Param2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
	int32 Param3;
};
