// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCardStoneRenderer.h"

// Sets default values
AJSCardStoneRenderer::AJSCardStoneRenderer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJSCardStoneRenderer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJSCardStoneRenderer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJSCardStoneRenderer::UpdateCardInfo(const FCardInfoData InData)
{
}

