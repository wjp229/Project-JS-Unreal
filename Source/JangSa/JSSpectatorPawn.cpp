// Fill out your copyright notice in the Description page of Project Settings.


#include "JSSpectatorPawn.h"

#include "JSCameraComponent.h"

AJSSpectatorPawn::AJSSpectatorPawn(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bAddDefaultMovementBindings = false;
	JsCameraComponent = CreateDefaultSubobject<UJSCameraComponent>(TEXT("Camera"));
}
