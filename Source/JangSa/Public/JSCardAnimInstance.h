// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "JSCardAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSCardAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Card)
	uint8 bIsGrabbed : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Card)
	uint8 bIsActivated : 1;

	TObjectPtr<class AJSCard> CardState;
	
protected:
	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
