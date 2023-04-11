// Fill out your copyright notice in the Description page of Project Settings.


#include "JSCard.h"

#include "JSGameState.h"

AJSCard::AJSCard()
{
}

const FCardData* AJSCard::GetCardInfo() const
{
	return CardData;
}

void AJSCard::InitCard(FCardData* InCardData)
{
	CardData = InCardData;
}

// Called when the game starts or when spawned
void AJSCard::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJSCard::OnActivateCardEffect(int InOrder)
{
	
}

void AJSCard::AddRemainTurn(int Value)
{
	RemainTurn += Value;

	// Set GUI For Remain Turn
}

void AJSCard::OnDestroyCard()
{
	this->Destroy();
}

void AJSCard::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Bind Delegate to GameState
	AJSGameState* GameState = Cast<AJSGameState>(GetWorld()->GetGameState());
	if(nullptr != GameState)
	{
		GameState->NotifyActivateCardEffect.AddDynamic(this, &AJSCard::OnActivateCardEffect);
		GameState->NotifyDestroyCard.AddDynamic(this, &AJSCard::OnDestroyCard);
		GameState->NotifyAddRemainCardTurn.AddDynamic(this, &AJSCard::AddRemainTurn);
		
		UE_LOG(LogTemp, Log, TEXT("Binding Events Has Succeeded!!"))
	}
	
	// Set Card GUI
	
	
	// 
}

