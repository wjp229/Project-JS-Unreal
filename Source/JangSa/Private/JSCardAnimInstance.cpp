// Fill out your copyright notice in the Description page of Project Settings.


#include "JSCardAnimInstance.h"

#include "Card/JSCard.h"

void UJSCardAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CardState = Cast<AJSCard>(GetOwningActor());
}

void UJSCardAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(nullptr != CardState)
	{
		bIsGrabbed = CardState->bIsGrabbed;
		bIsActivated = CardState->bIsActivated;
	}
}
