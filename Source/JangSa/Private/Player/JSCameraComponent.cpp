// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/JSCameraComponent.h"

UJSCameraComponent::UJSCameraComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	InitFOV = 50;

	UCameraComponent::SetFieldOfView(InitFOV);

	FVector InitLocation = FVector(320.0f, 440.0f, 190.0f);
	FRotator InitRotation = FRotator(-50.0f, 180.0f, 0.0f);
	SetRelativeLocation(InitLocation);
	SetRelativeRotation(InitRotation);
	SetAspectRatio(1920.0f / 1080.0f);
	SetOrthoWidth(1320.0f);
}