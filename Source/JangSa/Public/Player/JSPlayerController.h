// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API AJSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AJSPlayerController(const FObjectInitializer& ObjectInitializer);
	
protected:
	UPROPERTY()
	class UJSInput* InputHandler;
	
	//Deprecated
	void OnZKeyPressed();
	
public:
	virtual void SetupInputComponent() override;
};
