// Fill out your copyright notice in the Description page of Project Settings.


#include "JSCard.h"

#include "JSGameState.h"
#include "UObject/ConstructorHelpers.h"

AJSCard::AJSCard()
{
	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Card"));
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> M_CARD(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (M_CARD.Succeeded())
	{
	 	CardMesh->SetStaticMesh(M_CARD.Object);
	}
	
	RootComponent = CardMesh;
}

FCardInfoData AJSCard::GetCardInfo() const
{
	return CardData;
}

void AJSCard::InitCard(const FCardInfoData& InCardData)
{
	CardData = InCardData;
	UE_LOG(LogTemp, Log, TEXT("Card %s has Created!!"), *CardData.Name);
}

// Called when the game starts or when spawned
void AJSCard::BeginPlay()
{
	Super::BeginPlay();
}

void AJSCard::OnActivateCardEffect(int32 InOrder)
{
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

void AJSCard::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Bind Delegate to GameState
	AJSGameState* GameState = Cast<AJSGameState>(GetWorld()->GetGameState());
	if (nullptr != GameState)
	{
		GameState->NotifyActivateCardEffect.AddDynamic(this, &AJSCard::OnActivateCardEffect);
		GameState->NotifyDestroyCard.AddDynamic(this, &AJSCard::OnDestroyCard);
		GameState->NotifyAddRemainCardTurn.AddDynamic(this, &AJSCard::AddRemainTurn);


		UE_LOG(LogTemp, Log, TEXT("Binding Events Has Succeeded!!"))
	}

	// Set Card GUI


	// 
}
