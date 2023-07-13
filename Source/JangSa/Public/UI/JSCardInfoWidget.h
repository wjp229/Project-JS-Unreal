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
	void InitCardInfoWidget(const FCardInfoData& InCardInfoData);

	UFUNCTION(BlueprintNativeEvent)
	void ShowCardInfoWidget();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CardInfo")
	FCardInfoData CardInfoData;

private:
};
