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

	virtual void Tick(float DeltaSeconds) override;

	// Input Action Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(AllowPrivateAccess))
	TObjectPtr<class UJSControlData> ControlData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(AllowPrivateAccess))
	TObjectPtr<class UInputAction> PressAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(AllowPrivateAccess))
	TObjectPtr<class UInputAction> ReleaseAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(AllowPrivateAccess))
	TObjectPtr<class UInputAction> DragAction;

private:
	virtual void SetupInputComponent() override;

	void OnTapPressed();
	void OnTapReleased();
	void OnDrag();
	
	AActor* GetHitActor(const FVector2d& ScreenPosition) const;
	void SetMappingContext() const;

	// Interaction Section
private:
	UPROPERTY(VisibleAnywhere, Category="Interaction")
	TObjectPtr<AActor> SelectedObject;

	UPROPERTY(VisibleAnywhere, Category="Interaction")
	TObjectPtr<AActor> DetectedObject;


private:
	FVector2d GetCurrentMousePosition() const;
};
