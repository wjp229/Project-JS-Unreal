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

	// Input Action Section
protected:
	UPROPERTY()
	TObjectPtr<class UJSControlData> ControlData;

	UPROPERTY()
	TObjectPtr<class UInputAction> PressAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> ReleaseAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> DragAction;

private:
	virtual void SetupInputComponent() override;

	void OnTapPressed();
	void OnTapReleased();
	void OnDrag();
	
	AActor* GetHitActor(const FVector2d& ScreenPosition);
	void SetMappingContext() const;

	// Interaction Section
private:
	UPROPERTY(VisibleAnywhere, Category="Interaction")
	TObjectPtr<AActor> SelectedObject;

private:
	FVector2d GetCurrentMousePosition();
};
