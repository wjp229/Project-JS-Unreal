// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UUserWidget> StartMenuWidget;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UUserWidget> MainHUDWidget;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UJSShopWidget> JSShopWidget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UJSCardInfoWidget> CardInfoWidget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UJSResultWidget> ResultWidget;
	
protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	
};
