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

	KeycapMesh->BodyInstance.bLockRotation = true;
	UE_LOG(LogTemp, Log, TEXT("Mesh Rotation Constraint %d"), KeycapMesh->BodyInstance.bLockRotation);
}

FCardInfoData AJSCard::GetCardInfo() const
{
	return CardData;
}

void AJSCard::InitCard(const FCardInfoData& InCardData, int32 InObjectID, UJSCardEffectComponent* InEffectComponent)
{
	CardData = InCardData;
	CardObjID = InObjectID;
	CardState = ECardState::Inventory;
	
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
}

void AJSCard::OnActivateCardEffect(int32 InOrder)
{
	if(EffectComponent != nullptr)
	{
		EffectComponent->OnActivateEffect();
	}
}

bool AJSCard::OnSelectActor()
{
	if(CardState == ECardState::Inventory)
		return false;
	
	KeycapMesh->GetBodyInstance()->bLockTranslation = false;

	KeycapMesh->BodyInstance.SetEnableGravity(false);

	return true;
}

void AJSCard::OnReleaseActor()
{
	KeycapMesh->BodyInstance.SetEnableGravity(true);

	KeycapMesh->GetBodyInstance()->bLockTranslation = true;
}

void AJSCard::SetPossessCard(bool isPossessed)
{
	bIsSelected = isPossessed;
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
