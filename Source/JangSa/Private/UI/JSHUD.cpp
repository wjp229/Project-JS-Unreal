// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JSHUD.h"
#include "Components/WidgetComponent.h"
#include "UI/JSCardInfoWidget.h"
#include "UI/JSEventWidget.h"
#include "UI/JSResultWidget.h"
#include "UI/JSShopWidget.h"
#include "UObject/ConstructorHelpers.h"

AJSHUD::AJSHUD()
{
	const ConstructorHelpers::FClassFinder<UUserWidget> StartWidgetRef(TEXT("/Game/UI/BW_StartMenu.BW_StartMenu_C"));
	if (StartWidgetRef.Class != nullptr)
	{
		StartMenuWidget = CreateWidget<UUserWidget>(GetWorld(), StartWidgetRef.Class);
	}

	const ConstructorHelpers::FClassFinder<UUserWidget> HUDWidgetRef(TEXT("/Game/UI/BW_HUD.BW_HUD_C"));
	if (HUDWidgetRef.Class != nullptr)
	{
		MainHUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetRef.Class);
	}

	const ConstructorHelpers::FClassFinder<UJSShopWidget> ShopWidgetRef(TEXT("/Game/UI/BW_ShopWindow.BW_ShopWindow_C"));
	if (ShopWidgetRef.Class != nullptr)
	{
		JSShopWidget = CreateWidget<UJSShopWidget>(GetWorld(), ShopWidgetRef.Class);
	}

	const ConstructorHelpers::FClassFinder<UJSCardInfoWidget> CardInfoWidgetRef(TEXT("/Game/UI/BW_JSCardInfo.BW_JSCardInfo_C"));
	if (ShopWidgetRef.Class != nullptr)
	{
		CardInfoWidget = CreateWidget<UJSCardInfoWidget>(GetWorld(), CardInfoWidgetRef.Class);
	}

	const ConstructorHelpers::FClassFinder<UJSResultWidget> DefeatWidgetRef(TEXT("/Game/UI/BW_DefeatWidget.BW_DefeatWidget_C"));
	if (DefeatWidgetRef.Class != nullptr)
	{
		ResultWidget = CreateWidget<UJSResultWidget>(GetWorld(), DefeatWidgetRef.Class);
	}

	const ConstructorHelpers::FClassFinder<UJSEventWidget> EventWidgetRef(TEXT("/Game/UI/BW_EventInfo.BW_EventInfo_C"));
	if (EventWidgetRef.Class != nullptr)
	{
		EventWidget = CreateWidget<UJSEventWidget>(GetWorld(), EventWidgetRef.Class);
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

void AJSHUD::ShowCardInfoWidget(const FCardInfoData& InCardInfo, const float MousePositionX, const float MousePositionY, const bool InActive)
{
	if(nullptr != CardInfoWidget)
	{
		if(InActive)
		{
			if (!CardInfoWidget->IsInViewport())
			{
				CardInfoWidget->AddToViewport();
			}
			else
			{
				CardInfoWidget->SetVisibility(ESlateVisibility::Visible);

			}
			CardInfoWidget->InitCardInfoWidget(InCardInfo, MousePositionX, MousePositionY);
		}
		else
		{
			CardInfoWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AJSHUD::ShowDefeatWidget()
{
	if (!ResultWidget->IsInViewport())
	{
		ResultWidget->AddToViewport();
	}
		
	ResultWidget->ShowDefeatWidget();
}

void AJSHUD::ShowResultInfoWidget()
{
}

void AJSHUD::ShowEventInfoWidget(UJSEventData* InEventData)
{
	if (!EventWidget->IsInViewport())
	{
		EventWidget->AddToViewport();
	}

	EventWidget->SetVisibility(ESlateVisibility::Visible);
	EventWidget->InitEventInfoWidget(InEventData);
}

void AJSHUD::CloseEventInfoWidget()
{
	EventWidget->SetVisibility(ESlateVisibility::Hidden);
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
