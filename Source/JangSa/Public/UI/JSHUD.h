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

	void InitializeShop(const TArray<struct FCardInfoData*> InCardInfo);
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UJSShopWidget> JSShopWidget;

	
protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	
};
