// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/JSSpectatorPawn.h"
#include "JSGameMode.h"
#include "Player/JSCameraComponent.h"

#include "Engine/LocalPlayer.h"

AJSSpectatorPawn::AJSSpectatorPawn(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bAddDefaultMovementBindings = false;
	JsCameraComponent = CreateDefaultSubobject<UJSCameraComponent>(TEXT("Camera"));
	// Set CameraRot
}

void AJSSpectatorPawn::BeginPlay()
{
	Super::BeginPlay();
}


