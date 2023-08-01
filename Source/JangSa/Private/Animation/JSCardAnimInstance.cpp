// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/JSCardAnimInstance.h"
#include "Card/JSCard.h"

void UJSCardAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CardState = Cast<AJSCard>(GetOwningActor());
}

void UJSCardAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	/* Update Animation State depending on CardState */
	if(nullptr != CardState)
	{
		bIsGrabbed = CardState->bIsGrabbed;
		bIsActivated = CardState->bIsActivated;
	}
}
