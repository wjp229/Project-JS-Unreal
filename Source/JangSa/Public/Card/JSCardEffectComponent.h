// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JSCardEffectComponent.generated.h"


UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class JANGSA_API UJSCardEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJSCardEffectComponent();

	UFUNCTION(BlueprintImplementableEvent)
	int32 OnActivateEffect();

	UFUNCTION(BlueprintNativeEvent)
	int32 GetEffectResult();
};
