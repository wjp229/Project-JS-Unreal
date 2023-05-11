// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "JSSpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API AJSSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	AJSSpectatorPawn(const FObjectInitializer & ObjectInitializer);

private:
	UPROPERTY(Category = CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UJSCameraComponent> JsCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Action, meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UJSControlData> ControlData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Action, meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UInputAction> ClickAction;

	
protected:
	virtual void BeginPlay() override;
	void SetMappingContext();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void Test();
};
