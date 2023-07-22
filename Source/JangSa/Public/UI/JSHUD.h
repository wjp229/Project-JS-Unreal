// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/JSEventData.h"
#include "Data/JSTypes.h"
#include "GameFramework/HUD.h"
#include "JSHUD.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API AJSHUD : public AHUD
{
	GENERATED_BODY()

public:
	AJSHUD();

	UFUNCTION(BlueprintCallable)
	void DrawMainHUD();

	void EnableTurnEndButton();
	
	// Interaction about Shop
	void InitializeShop(const TArray<struct FCardInfoData*> InCardInfo, bool bIsInitPhase);

	// Interaction about Card Info
	void ShowCardInfoWidget(const FCardInfoData& InCardInfo, const bool InActive);
	
	void ShowDefeatWidget();

	void ShowResultInfoWidget(FPlayerData& InData);

	void ShowEventInfoWidget(UJSEventData* InEventData);
	void CloseEventInfoWidget();

	
private:
	TObjectPtr<UUserWidget> StartMenuWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StartMenuWidgetClass;
	
	TObjectPtr<class UJSMainWidget> MainHUDWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainHUDWidgetClass;
	
	TObjectPtr<class UJSShopWidget> JSShopWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJSShopWidget> JSShopWidgetClass;

	TObjectPtr<class UJSCardInfoWidget> CardInfoWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJSCardInfoWidget> CardInfoWidgetClass;

	TObjectPtr<class UJSDefeatWidget> DefeatWidget;

	TObjectPtr<class UJSResultWidget> ResultWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJSDefeatWidget> ResultWidgetClass;

	TObjectPtr<class UJSEventWidget> EventWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJSEventWidget> EventWidgetClass;

	TObjectPtr<class UPhaseAlarmWidget> PhaseAlarmWidget;

	FTimerHandle ScaleHandler;
	FTimerHandle PhaseHandler;
	FTimerHandle MoveHandler;

protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	void SetWidgetScale(UUserWidget* InWidget, float InScaleSpeed, bool IsDirectionX);
	void SetWidgetPosition(UUserWidget* InWidget, FVector2D InitPos, float InMoveSpeed);

	void CloseAllUserWidget();
};
