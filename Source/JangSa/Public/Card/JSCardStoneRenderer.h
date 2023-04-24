// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/JSCardRenderInterface.h"
#include "JSCardStoneRenderer.generated.h"

UCLASS()
class JANGSA_API AJSCardStoneRenderer : public AActor, public IJSCardRenderInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJSCardStoneRenderer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UpdateCardInfo(const FCardInfoData InData) override;

};
