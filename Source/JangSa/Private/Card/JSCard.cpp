// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCard.h"
#include "Card/JSCardEffectComponent.h"
#include "JSGameState.h"
#include "UI/JSHUD.h"
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

void AJSCard::SetCardStateActive(bool Active)
{
	// Bind Delegate to GameState
	AJSGameState* const NewGameState = GetWorld()->GetGameState<AJSGameState>();
	if (nullptr != NewGameState)
	{
		if(Active)
		{
			NewGameState->NotifyActivateCardEffect.AddDynamic(this, &AJSCard::OnActivateCardEffect);
		}
		else
		{
			NewGameState->NotifyActivateCardEffect.RemoveDynamic(this, &AJSCard::OnActivateCardEffect);
		}
	}
}

bool AJSCard::OnSelectActor()
{
	if(CardState == ECardState::Inventory)
		return false;

	OriginPosition = GetActorLocation();
	
	KeycapMesh->GetBodyInstance()->bLockTranslation = false;

	KeycapMesh->BodyInstance.SetEnableGravity(false);

	return true;
}

void AJSCard::OnReleaseActor()
{
	// Check If Card is on right place else go back to origin Place
	if(!bIsPlaceable)
	{
		SetActorLocation(OriginPosition);
	}
	else
	{
		
	}
	
	KeycapMesh->BodyInstance.SetEnableGravity(true);

	KeycapMesh->GetBodyInstance()->bLockTranslation = true;
}

void AJSCard::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();

	OnMouseEnterActor();
}

void AJSCard::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();

	OnMouseExitActor();
}

void AJSCard::OnMouseEnterActor()
{
	// To do : Activate Info HUD After few seconds
}


void AJSCard::OnMouseExitActor()
{
	// To do : Deactivate Info HUD After few Seconds
}

void AJSCard::ActivateCardInfoHUD()
{
	
}

void AJSCard::SetPossessCard(bool IsPossessed)
{
	bIsSelected = IsPossessed;
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
