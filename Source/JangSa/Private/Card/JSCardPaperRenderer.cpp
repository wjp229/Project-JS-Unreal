// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCardPaperRenderer.h"

// Sets default values
AJSCardPaperRenderer::AJSCardPaperRenderer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJSCardPaperRenderer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJSCardPaperRenderer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJSCardPaperRenderer::UpdateCardInfo(const FCardInfoData InData)
{
}

