// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/JSEventData.h"
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
	
	// Interaction about Shop
	void InitializeShop(const TArray<struct FCardInfoData*> InCardInfo);

	// Interaction about Card Info
	void ShowCardInfoWidget(const FCardInfoData& InCardInfo, const float MousePositionX, const float MousePositionY, const bool InActive);
	
	void ShowDefeatWidget();

	void ShowResultInfoWidget();

	void ShowEventInfoWidget(UJSEventData* InEventData);
	void CloseEventInfoWidget();

	
private:
	TObjectPtr<UUserWidget> StartMenuWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StartMenuWidgetClass;
	
	TObjectPtr<UUserWidget> MainHUDWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainHUDWidgetClass;
	
	TObjectPtr<class UJSShopWidget> JSShopWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJSShopWidget> JSShopWidgetClass;

	TObjectPtr<class UJSCardInfoWidget> CardInfoWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJSCardInfoWidget> CardInfoWidgetClass;

	TObjectPtr<class UJSResultWidget> ResultWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJSResultWidget> ResultWidgetClass;

	TObjectPtr<class UJSEventWidget> EventWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJSEventWidget> EventWidgetClass;

protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	
};
