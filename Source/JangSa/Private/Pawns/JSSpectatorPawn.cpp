// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/JSSpectatorPawn.h"
#include "Player/JSCameraComponent.h"

AJSSpectatorPawn::AJSSpectatorPawn(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bAddDefaultMovementBindings = false;
	JsCameraComponent = CreateDefaultSubobject<UJSCameraComponent>(TEXT("Camera"));

	// Set CameraRot
}
