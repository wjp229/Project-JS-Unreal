// Fill out your copyright notice in the Description page of Project Settings.


#include "JSPlayerController.h"
#include "JSGameState.h"
#include "JSInput.h"

// AJSPlayerController::AJSPlayerController(const FObjectInitializer& ObjectInitializer)
// 	:Super(ObjectInitializer)
// {
// 	
// }

void AJSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputHandler = NewObject<UJSInput>(this);
	
	InputComponent->BindAction(TEXT("ZKey"), IE_Pressed, this, &AJSPlayerController::OnZKeyPressed);
}

void AJSPlayerController::OnZKeyPressed()
{
	AJSGameState* const MyGameState = GetWorld()->GetGameState<AJSGameState>();

	if(MyGameState != nullptr)
	{
		MyGameState->SetNextTurn();
	}
}