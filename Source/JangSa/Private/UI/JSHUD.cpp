// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JSHUD.h"
#include "UI/JSCardInfoWidget.h"
#include "UI/JSEventWidget.h"
#include "UI/JSDefeatWidget.h"
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

	const ConstructorHelpers::FClassFinder<UJSCardInfoWidget> CardInfoWidgetRef(
		TEXT("/Game/UI/BW_JSCardInfo.BW_JSCardInfo_C"));
	if (ShopWidgetRef.Class != nullptr)
	{
		CardInfoWidget = CreateWidget<UJSCardInfoWidget>(GetWorld(), CardInfoWidgetRef.Class);
	}

	const ConstructorHelpers::FClassFinder<UJSDefeatWidget> DefeatWidgetRef(
		TEXT("/Game/UI/BW_DefeatWidget.BW_DefeatWidget_C"));
	if (DefeatWidgetRef.Class != nullptr)
	{
		DefeatWidget = CreateWidget<UJSDefeatWidget>(GetWorld(), DefeatWidgetRef.Class);
	}

	const ConstructorHelpers::FClassFinder<UJSResultWidget> ResultWidgetRef(
		TEXT("/Game/UI/BW_ResultWidget.BW_ResultWidget_C"));
	if (ResultWidgetRef.Class != nullptr)
	{
		ResultWidget = CreateWidget<UJSResultWidget>(GetWorld(), ResultWidgetRef.Class);
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

void AJSHUD::ShowCardInfoWidget(const FCardInfoData& InCardInfo, const bool InActive)
{
	if (nullptr != CardInfoWidget)
	{
		if (InActive)
		{
			if (!CardInfoWidget->IsInViewport())
			{
				CardInfoWidget->AddToViewport();
			}
			else
			{
				CardInfoWidget->SetVisibility(ESlateVisibility::Visible);
			}
			CardInfoWidget->InitCardInfoWidget(InCardInfo);
		}
		else
		{
			CardInfoWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AJSHUD::ShowDefeatWidget()
{
	CloseAllUserWidget();

	if (!DefeatWidget->IsInViewport())
	{
		DefeatWidget->AddToViewport();
	}

	DefeatWidget->ShowDefeatWidget();
}

void AJSHUD::ShowResultInfoWidget(FPlayerData& InData)
{
	CloseAllUserWidget();

	if (!ResultWidget->IsInViewport())
	{
		ResultWidget->AddToViewport();
		ResultWidget->InitResultWidget(InData);
	}
}

void AJSHUD::ShowEventInfoWidget(UJSEventData* InEventData)
{
	if (!EventWidget->IsInViewport())
	{
		EventWidget->AddToViewport();
	}

	EventWidget->SetVisibility(ESlateVisibility::Visible);
	EventWidget->InitEventInfoWidget(InEventData);

	SetWidgetScale(EventWidget, .03f);
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

void AJSHUD::SetWidgetScale(UUserWidget* InWidget, float InScaleSpeed)
{
	InWidget->SetRenderScale(FVector2D(1.f, 0.f));
	
	ScaleHandler.Invalidate();

	GetWorld()->GetTimerManager().SetTimer(ScaleHandler, FTimerDelegate::CreateLambda([this, InWidget, InScaleSpeed]()
	{
		float YValue = InWidget->GetRenderTransform().Scale.Y;
		if(YValue >= 1.f) return;

		YValue += InScaleSpeed;
		EventWidget->SetRenderScale(FVector2D(1.f, YValue));

	}), .002f, true);
}

void AJSHUD::SetWidgetPosition(UUserWidget* InWidget, FVector2D InitPos, float InMoveSpeed)
{
}

void AJSHUD::CloseAllUserWidget()
{
	MainHUDWidget->SetVisibility(ESlateVisibility::Hidden);
	JSShopWidget->SetVisibility(ESlateVisibility::Hidden);
	CardInfoWidget->SetVisibility(ESlateVisibility::Hidden);
	EventWidget->SetVisibility(ESlateVisibility::Hidden);
}
