// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/CardInfoRowBase.h"
#include "JSShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSShopWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitShop(TArray<FCardInfoData*> InShopCards);
	
	UFUNCTION(BlueprintNativeEvent)
	void InitCardInfoInShop();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Card)
	TArray<FCardInfoData> ShopCards;
	
	UFUNCTION(BlueprintCallable)
	void RerollShop();

	UFUNCTION(BlueprintCallable)
	bool ClickPurchaseCardButton(int32 InButtonNum);
};
