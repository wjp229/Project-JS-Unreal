// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "JSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API AJSGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AJSGameMode();

	virtual void PostInitializeComponents() override;
	
private:
	UFUNCTION()
	void TestBinding(int32 num);
};
