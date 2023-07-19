// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JSShopWidget.h"

#include "JSGameState.h"
#include "Data/CardInfoRowBase.h"

void UJSShopWidget::InitShop(TArray<FCardInfoData*> InShopCards)
{
	// Initialize Shop
	ShopCards.Empty();
	
	for(int ix = 0; ix < 4; ix++)
	{
		ShopCards.Emplace(*InShopCards[ix]);
	}
	
	InitCardInfoInShop();
}

void UJSShopWidget::RerollShop()
{
	AJSGameState* JSGameState = Cast<AJSGameState>(GetWorld()->GetGameState());
	if(JSGameState != nullptr)
	{
		// Logic about Purchase
		JSGameState->OnResetShop(false);
	}
}

bool UJSShopWidget::ClickPurchaseCardButton(int32 InButtonNum)
{
	AJSGameState* JSGameState = Cast<AJSGameState>(GetWorld()->GetGameState());
	if(JSGameState != nullptr)
	{
		// Logic about Purchase
		if(JSGameState->PurchaseCard(ShopCards[InButtonNum].Id))
			return true;
	}

	return false;
}

void UJSShopWidget::ExitShop()
{
	AJSGameState* JSGameState = Cast<AJSGameState>(GetWorld()->GetGameState());
	if(JSGameState != nullptr)
	{
		JSGameState->ExitShop();
	}
}

void UJSShopWidget::FoldShop(bool bIsFolded)
{
	AJSGameState* JSGameState = Cast<AJSGameState>(GetWorld()->GetGameState());
	if(JSGameState != nullptr)
	{
		JSGameState->FoldShop(bIsFolded);
	}
}

void UJSShopWidget::InitCardInfoInShop_Implementation()
{
}
