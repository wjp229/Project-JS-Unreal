// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/CardInfoRowBase.h"
#include "JSCardInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSCardInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitCardInfoWidget(const FCardInfoData& InCardInfoData, const float MousePositionX, const float MousePositionY);

	UFUNCTION(BlueprintNativeEvent)
	void ShowCardInfoWidget(const FVector2D CurrentMousePosition);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CardInfo")
	FCardInfoData CardInfoData;

private:
};
