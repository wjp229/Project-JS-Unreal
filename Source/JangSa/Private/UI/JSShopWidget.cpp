// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JSShopWidget.h"

#include "Data/CardInfoRowBase.h"

void UJSShopWidget::InitShop(TArray<FCardInfoData*> InShopCards)
{
	// Initialize Shop
	CardNames.Empty();

	for(int ix = 0; ix < 4; ix++)
	{

		//ShopCards[ix] = InShopCards[ix];
		CardNames.Emplace(InShopCards[ix]->Name);

		//UE_LOG(LogTemp, Log, TEXT("%s In the Shop!!"), *ShopCards[ix].Name);
		
	}
	
	InitCardInfoInShop();
}

void UJSShopWidget::InitCardInfoInShop_Implementation()
{
}

void UJSShopWidget::ClickPurchaseCardButton()
{
}
