// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCardHoldZone.h"
#include "Card/JSCard.h"

AJSCardHoldZone::AJSCardHoldZone()
{
}

void AJSCardHoldZone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorBeginOverlap.AddDynamic(this, &AJSCardHoldZone::OnCardBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AJSCardHoldZone::OnCardEndOverlap);
}

void AJSCardHoldZone::OnCardBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	AJSCard* InCard = Cast<AJSCard>(OtherActor);
	if(nullptr != InCard)
	{
		InCard->SlotNum = -2;
		InCard->bIsPlaceable = true;
	}
}

void AJSCardHoldZone::OnCardEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	AJSCard* InCard = Cast<AJSCard>(OtherActor);
	if(nullptr != InCard)
	{
		InCard->SlotNum = -1;
		InCard->bIsPlaceable = false;
	}
}
