// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCard.h"
#include "JSGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/JSRenderManager.h"

UJSCard::UJSCard()
{
	CardRenderState = ECardRenderState::Stone;
}

FCardInfoData UJSCard::GetCardInfo() const
{
	return CardData;
}

void UJSCard::InitCard(const FCardInfoData& InCardData, int32 InObjectID)
{
	CardData = InCardData;
	CardObjID = InObjectID;

	// Bind Delegate to GameState
	AJSGameState* NewGameState = Cast<AJSGameState>(GetWorld()->GetGameState());
	if (nullptr != NewGameState)
	{
		NewGameState->NotifyActivateCardEffect.AddDynamic(this, &UJSCard::OnActivateCardEffect);
		NewGameState->NotifyDestroyCard.AddDynamic(this, &UJSCard::OnDestroyCard);
		NewGameState->NotifyAddRemainCardTurn.AddDynamic(this, &UJSCard::AddRemainTurn);
	}

	UE_LOG(LogTemp, Log, TEXT("Card %s has Created!!"), *CardData.Name);

	// Init Card Renderers
	// UJSRenderManager* RenderManager = UJSRenderManager::GetInstance();
	// RenderManager->SpawnCardRenderer(CardObjID, CardRenderState, CardData);
	
}

void UJSCard::OnActivateCardEffect(int32 InOrder)
{
}

void UJSCard::AddRemainTurn(int32 Value)
{
	RemainTurn += Value;

	// Set GUI For Remain Turn
}

void UJSCard::OnDestroyCard()
{
	//this->Destroy();
}
