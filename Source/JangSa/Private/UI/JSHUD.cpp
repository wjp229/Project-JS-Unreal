// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JSHUD.h"
#include "UI/JSCardInfoWidget.h"
#include "UI/JSEventWidget.h"
#include "UI/JSDefeatWidget.h"
#include "UI/JSResultWidget.h"
#include "UI/JSShopWidget.h"
#include "UI/PhaseAlarmWidget.h"
#include "UI/JSMainWidget.h"
#include "UObject/ConstructorHelpers.h"

AJSHUD::AJSHUD()
{
	const ConstructorHelpers::FClassFinder<UUserWidget> StartWidgetRef(TEXT("/Game/UI/BW_StartMenu.BW_StartMenu_C"));
	if (StartWidgetRef.Class != nullptr)
	{
		StartMenuWidget = CreateWidget<UUserWidget>(GetWorld(), StartWidgetRef.Class);
	}

	const ConstructorHelpers::FClassFinder<UJSMainWidget> HUDWidgetRef(TEXT("/Game/UI/BW_HUD.BW_HUD_C"));
	if (HUDWidgetRef.Class != nullptr)
	{
		MainHUDWidget = CreateWidget<UJSMainWidget>(GetWorld(), HUDWidgetRef.Class);
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

	const ConstructorHelpers::FClassFinder<UPhaseAlarmWidget> PhaseAlarmRef(
		TEXT("/Game/UI/BW_PhaseAlarm.BW_PhaseAlarm_C"));
	if (PhaseAlarmRef.Class != nullptr)
	{
		PhaseAlarmWidget = CreateWidget<UPhaseAlarmWidget>(GetWorld(), PhaseAlarmRef.Class);
	}
}

void AJSHUD::InitializeShop(const TArray<FCardInfoData*> InCardInfo, bool bIsInitPhase)
{
	if (bIsInitPhase)
	{
		PhaseAlarmWidget->SetPhaseText(TEXT("상점 페이즈"));
		PhaseAlarmWidget->SetVisibility(ESlateVisibility::Visible);
		SetWidgetScale(PhaseAlarmWidget, .005f, false);
	}

	if (!JSShopWidget->IsInViewport())
	{
		JSShopWidget->AddToViewport();
		JSShopWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	JSShopWidget->InitShop(InCardInfo);

	if(bIsInitPhase)
	{
		PhaseHandler.Invalidate();

		GetWorld()->GetTimerManager().SetTimer(PhaseHandler, FTimerDelegate::CreateLambda([this]()
		{
			PhaseAlarmWidget->SetVisibility(ESlateVisibility::Hidden);
			JSShopWidget->SetVisibility(ESlateVisibility::Visible);
			SetWidgetScale(JSShopWidget, .03f, true);

		}), .002f, false, 1.5f);
	}
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
	PhaseAlarmWidget->SetPhaseText(TEXT("이벤트 페이즈"));
	PhaseAlarmWidget->SetVisibility(ESlateVisibility::Visible);
	SetWidgetScale(PhaseAlarmWidget, .005f, false);

	if (!EventWidget->IsInViewport())
	{
		EventWidget->AddToViewport();
		EventWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	EventWidget->InitEventInfoWidget(InEventData);

	PhaseHandler.Invalidate();

	GetWorld()->GetTimerManager().SetTimer(PhaseHandler, FTimerDelegate::CreateLambda([this]()
	{
		PhaseAlarmWidget->SetVisibility(ESlateVisibility::Hidden);
		EventWidget->SetVisibility(ESlateVisibility::Visible);
		SetWidgetScale(EventWidget, .03f, true);

		UE_LOG(LogTemp, Log, TEXT("HIO"));
	}), .002f, false, 1.5f);
}

void AJSHUD::CloseEventInfoWidget()
{
	EventWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AJSHUD::DrawMainHUD()
{
	MainHUDWidget->AddToViewport();

	PhaseAlarmWidget->AddToViewport();
	PhaseAlarmWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AJSHUD::EnableTurnEndButton()
{
	MainHUDWidget->EnableTurnEndButton();
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

void AJSHUD::SetWidgetScale(UUserWidget* InWidget, float InScaleSpeed, bool IsDirectionX)
{
	InWidget->SetRenderScale(FVector2D(1.f, 0.f));

	ScaleHandler.Invalidate();

	GetWorld()->GetTimerManager().SetTimer(ScaleHandler, FTimerDelegate::CreateLambda([this, InWidget, InScaleSpeed]()
	{
		float YValue = InWidget->GetRenderTransform().Scale.Y;
		if (YValue >= 1.f)
		{
			GetWorldTimerManager().ClearTimer(ScaleHandler);
			return;
		}
		YValue += InScaleSpeed;
		InWidget->SetRenderScale(FVector2D(1.f, YValue));
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
