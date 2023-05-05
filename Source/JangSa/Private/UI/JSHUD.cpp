// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JSHUD.h"
#include "Components/WidgetComponent.h"
#include "UI/JSShopWidget.h"
#include "UObject/ConstructorHelpers.h"

AJSHUD::AJSHUD()
{
	const ConstructorHelpers::FClassFinder<UJSShopWidget> ShopWidgetRef(TEXT("/Game/UI/BP_JSShop.BP_JSShop_C"));
	if(ShopWidgetRef.Class != nullptr)
	{
		JSShopWidget = CreateWidget<UJSShopWidget>(GetWorld(), ShopWidgetRef.Class);
	}
}

void AJSHUD::InitializeShop(const TArray<FCardInfoData*> InCardInfo)
{
	JSShopWidget->InitShop(InCardInfo);
}

void AJSHUD::BeginPlay()
{
	Super::BeginPlay();

	JSShopWidget->AddToViewport();
}

void AJSHUD::DrawHUD()
{
	Super::DrawHUD();
}
