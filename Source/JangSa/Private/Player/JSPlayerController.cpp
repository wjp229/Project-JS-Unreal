// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/JSPlayerController.h"
#include "JSGameState.h"
#include "Interfaces/JSInputInterface.h"
#include "Player/JSInput.h"
#include "UObject/ConstructorHelpers.h"
#include "InputMappingContext.h"

AJSPlayerController::AJSPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
}

void AJSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputHandler = NewObject<UJSInput>(this);
}

void AJSPlayerController::OnTapPressed(const FVector2D& ScreenPosition, float DownTime)
{

}

AActor* AJSPlayerController::GetHitActor(const FVector2d& ScreenPosition)
{
	FHitResult Hit;
	if (GetHitResultAtScreenPosition(ScreenPosition, ECC_Visibility, true, Hit))
	{
		UE_LOG(LogTemp, Log, TEXT("%s has Called!"), *Hit.GetActor()->GetName());
		return Hit.GetActor();
	}

	return nullptr;
}
