// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCard.h"
#include "Card/JSCardEffectComponent.h"
#include "JSGameState.h"
#include "Data/JSCardDataAsset.h"
#include "UI/JSHUD.h"
#include "UObject/ConstructorHelpers.h"

AJSCard::AJSCard()
{
	Keycap = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Keycap Mesh"));
	
	RootComponent = Keycap;
	Keycap->SetRelativeScale3D(FVector(.05f, .05f, .05f));
	Keycap->SetSimulatePhysics(false);

	RemainTurn = GetCardInfo().InitRemainTurn;
	CardState = ECardState::Holding;
}

FCardInfoData AJSCard::GetCardInfo() const
{
	return CardData;
}

void AJSCard::InitCard(const FCardInfoData& InCardData, int32 InObjectID, UJSCardDataAsset* InDataAsset)
{
	CardData = InCardData;
	CardObjID = InObjectID;
	CardState = ECardState::Inventory;

	if(nullptr == InDataAsset)
	{
		UE_LOG(LogTemp, Log, TEXT("Null Data Asset "));
		return;
	}
	
	UJSCardEffectComponent* CardEffectComponent = NewObject<UJSCardEffectComponent>(this, InDataAsset->EffectComponent);
	EffectComponent = CardEffectComponent;
	EffectComponent->RegisterComponent();

	// if(nullptr == KeycapMesh)
	// {
	// 	UE_LOG(LogTemp, Log, TEXT("Null Keycap Mesh "));
	// 	return;
	// }
	// USkeletalMeshComponent* CardEffectComponent = NewObject<USkeletalMeshComponent>(this, InDataAsset->EffectComponent);
	// EffectComponent = CardEffectComponent;
	// EffectComponent->RegisterComponent();
	Keycap->SetSkeletalMesh(InDataAsset->Mesh);

	SetActorLabel(*GetCardInfo().Name);
}

void AJSCard::ActivateCardEffect(int32 InOrder)
{
	if (EffectComponent != nullptr)
	{
		EffectComponent->OnActivateEffect();
		RemainTurn -= 1;
	}
}

void AJSCard::SetCardStateActive(bool Active)
{
	if (Active && CardState == ECardState::Activated)
	{
		return;
	}
	else if (!Active && CardState == ECardState::Holding)
	{
		return;
	}

	// Bind Delegate to GameState
	AJSGameState* const GameState = GetWorld()->GetGameState<AJSGameState>();
	if (nullptr != GameState)
	{
		if (Active)
		{
			// To do : Set Slot Num
			if (GameState->RegisterActivateCard(this, SlotNum))
			{
				CardState = ECardState::Activated;
			}
			else
			{
				SetActorLocation(OriginPosition);
			}
		}
		else
		{
			CardState = ECardState::Holding;
		}
	}
}

bool AJSCard::OnSelectActor()
{
	if (CardState == ECardState::Inventory)
		return false;

	OriginPosition = GetActorLocation();

	Keycap->BodyInstance.SetEnableGravity(false);

	return true;
}

void AJSCard::OnReleaseActor()
{
	// Check If Card is on right place else go back to origin Place
	if (!bIsPlaceable)
	{
		SetActorLocation(OriginPosition);
	}
	else
	{
		SetCardStateActive(true);
	}

	Keycap->BodyInstance.SetEnableGravity(true);
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
	if (RemainTurn == 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Destroy"));
	}
	//this->Destroy();
}
