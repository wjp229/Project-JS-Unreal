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
	
	void InitializeShop(const TArray<struct FCardInfoData*> InCardInfo, bool bIsInitPhase);
	void ShowCardInfoWidget(const FCardInfoData& InCardInfo, const bool InActive);
	void ShowDefeatWidget();
	void ShowResultInfoWidget(FPlayerData& InData);
	void ShowEventInfoWidget(UJSEventData* InEventData);
	
	void CloseEventInfoWidget();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UUserWidget> StartMenuWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StartMenuWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UJSMainWidget> MainHUDWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainHUDWidgetClass;

	TObjectPtr<class UJSShopWidget> JSShopWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJSShopWidget> JSShopWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UJSCardInfoWidget> CardInfoWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJSCardInfoWidget> CardInfoWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UJSDefeatWidget> DefeatWidget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UJSResultWidget> ResultWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJSDefeatWidget> ResultWidgetClass;

	TObjectPtr<class UJSEventWidget> EventWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJSEventWidget> EventWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UJSPhaseAlarmWidget> PhaseAlarmWidget;

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
