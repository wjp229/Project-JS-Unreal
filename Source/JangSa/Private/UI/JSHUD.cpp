// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JSHUD.h"
#include "Components/WidgetComponent.h"
#include "UI/JSCardInfoWidget.h"
#include "UI/JSShopWidget.h"
#include "UObject/ConstructorHelpers.h"

AJSHUD::AJSHUD()
{
	const ConstructorHelpers::FClassFinder<UUserWidget> StartWidgetRef(TEXT("/Game/UI/StartMenu.StartMenu_C"));
	if (StartWidgetRef.Class != nullptr)
	{
		StartMenuWidget = CreateWidget<UUserWidget>(GetWorld(), StartWidgetRef.Class);
	}

	const ConstructorHelpers::FClassFinder<UUserWidget> HUDWidgetRef(TEXT("/Game/UI/HUD.HUD_C"));
	if (HUDWidgetRef.Class != nullptr)
	{
		MainHUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetRef.Class);
	}

	const ConstructorHelpers::FClassFinder<UJSShopWidget> ShopWidgetRef(TEXT("/Game/UI/BP_JSShop.BP_JSShop_C"));
	if (ShopWidgetRef.Class != nullptr)
	{
		JSShopWidget = CreateWidget<UJSShopWidget>(GetWorld(), ShopWidgetRef.Class);
	}

	const ConstructorHelpers::FClassFinder<UJSCardInfoWidget> CardInfoWidgetRef(TEXT("/Game/UI/BW_JSCardInfo.BW_JSCardInfo_C"));
	if (ShopWidgetRef.Class != nullptr)
	{
		CardInfoWidget = CreateWidget<UJSCardInfoWidget>(GetWorld(), CardInfoWidgetRef.Class);
	}
	
}

void AJSHUD::InitializeShop(const TArray<FCardInfoData*> InCardInfo)
{
	if (!JSShopWidget->IsInViewport())
	{
		JSShopWidget->AddToViewport();
	}
	else
	{
		JSShopWidget->SetVisibility(ESlateVisibility::Visible);
	}
	JSShopWidget->InitShop(InCardInfo);
}

void AJSHUD::ShowCardInfoWidget(const FCardInfoData& InCardInfo, const float MousePositionX, const float MousePositionY)
{
	if(nullptr != CardInfoWidget)
	{
		if (!CardInfoWidget->IsInViewport())
		{
			CardInfoWidget->AddToViewport();

		}
		CardInfoWidget->InitCardInfoWidget(InCardInfo, MousePositionX, MousePositionY);
	}
}

void AJSHUD::DrawMainHUD()
{
	MainHUDWidget->AddToViewport();
}

void AJSHUD::BeginPlay()
{
	Super::BeginPlay();

	StartMenuWidget->AddToViewport();
}

void AJSHUD::DrawHUD()
{
	Super::DrawHUD();
}
