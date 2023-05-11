// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCard.h"

#include "JSCardEffectComponent.h"
#include "JSGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AJSCard::AJSCard()
{
	KeycapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeycapMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> KeycapMeshRef(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if(KeycapMeshRef.Succeeded())
	{
		KeycapMesh->SetStaticMesh(KeycapMeshRef.Object);
	}

	RootComponent = KeycapMesh;
	KeycapMesh->SetRelativeScale3D(FVector(.05f, .05f, .05f));
	KeycapMesh->SetSimulatePhysics(true);
}

FCardInfoData AJSCard::GetCardInfo() const
{
	return CardData;
}

void AJSCard::InitCard(const FCardInfoData& InCardData, int32 InObjectID, UJSCardEffectComponent* InEffectComponent)
{
	CardData = InCardData;
	CardObjID = InObjectID;

	// Bind Delegate to GameState
	AJSGameState* const NewGameState = GetWorld()->GetGameState<AJSGameState>();
	if (nullptr != NewGameState)
	{
		NewGameState->NotifyActivateCardEffect.AddDynamic(this, &AJSCard::OnActivateCardEffect);
		NewGameState->NotifyDestroyCard.AddDynamic(this, &AJSCard::OnDestroyCard);
		NewGameState->NotifyAddRemainCardTurn.AddDynamic(this, &AJSCard::AddRemainTurn);
	}

	EffectComponent = InEffectComponent;
	EffectComponent->RegisterComponent();
	
	UE_LOG(LogTemp, Log, TEXT("Card %s has Created!!"), *CardData.Name);

}

void AJSCard::OnInputTab_Implementation()
{
	IJSInputInterface::OnInputTab_Implementation();
}

void AJSCard::OnActivateCardEffect(int32 InOrder)
{
	UE_LOG(LogTemp, Log, TEXT("Acitvation On Card"));
	if(EffectComponent != nullptr)
	{
		EffectComponent->OnActivateEffect();
	}
}

void AJSCard::AddRemainTurn(int32 Value)
{
	RemainTurn += Value;

	// Set GUI For Remain Turn
}

void AJSCard::OnDestroyCard()
{
	//this->Destroy();
}
