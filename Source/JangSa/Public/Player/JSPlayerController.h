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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Action, meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UJSControlData> ControlData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Action, meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UInputAction> ClickAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Action, meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UInputAction> DragAction;

private:
	virtual void SetupInputComponent() override;

	void OnTapPressed();
	void OnDrag();
	
	void GetHitActor(const FVector2d& ScreenPosition);
	void SetMappingContext() const;

	TObjectPtr<AActor> SelectedObject;

private:
	FVector2d GetCurrentMousePosition();
};
