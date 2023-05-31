// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JSCardDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSCardDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category=Effect)
	TSubclassOf<class UJSCardEffectComponent> EffectComponent;

	UPROPERTY(EditAnywhere, Category=Mesh)
	TObjectPtr<class USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, Category=Mesh)
	TObjectPtr<UTexture> Texture;
};
