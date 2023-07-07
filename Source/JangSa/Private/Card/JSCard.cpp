// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCard.h"
#include "Animation/JSCardAnimInstance.h"
#include "Card/JSCardEffectComponent.h"
#include "JSGameState.h"
#include "Animation/AnimInstance.h"
#include "Data/JSCardDataAsset.h"
#include "Event/JSEventAction.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UI/JSHUD.h"
#include "UObject/ConstructorHelpers.h"

AJSCard::AJSCard()
{
	CaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Case Mesh"));
	KeycapMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Keycap Mesh"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		CaseMeshRef(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (CaseMeshRef.Succeeded())
	{
		CaseMesh->SetStaticMesh(CaseMeshRef.Object);
	}

	RootComponent = CaseMesh;
	CaseMesh->SetRelativeScale3D(FVector(.05f, .05f, .01f));
	CaseMesh->SetSimulatePhysics(false);

	KeycapMesh->SetupAttachment(CaseMesh);
	KeycapMesh->SetRelativeScale3D(FVector(.7f, .7f, 3.5f));
	KeycapMesh->SetRelativeRotation(FRotator(.0f, 270.0f, 0.f));
	KeycapMesh->SetRelativeLocation(FVector(.0f, .0f, 50.f));
	KeycapMesh->SetSimulatePhysics(false);

	CardState = ECardState::Inventory;

	// DefaultOutlineColor = FLinearColor(1.0f, 1.0f, 1.0f);
	// MouseEnterOutlineColor = FLinearColor(0.1f, 1.0f, 0.1f);
	// DisabledOutlineColor = FLinearColor(1.0f, 0.1f, 0.1f);
	// SelectOulineColor = FLinearColor(1.0f, 1.0f, 0.1f);
}


FCardInfoData AJSCard::GetCardInfo() const
{
	return CardData;
}

void AJSCard::InitCard(const FCardInfoData& InCardData, int32 InObjectID, UJSCardDataAsset* InDataAsset)
{
	CardData = InCardData;
	CardState = ECardState::Inventory;

	
	if (nullptr == InDataAsset)
	{
		UE_LOG(LogTemp, Log, TEXT("Null Data Asset "));
		return;
	}

	OnBeginCursorOver

	UJSCardEffectComponent* CardEffectComponent = NewObject<UJSCardEffectComponent>(this, InDataAsset->EffectComponent);
	EffectComponent = CardEffectComponent;
	EffectComponent->RegisterComponent();

	CaseMesh->SetSimulatePhysics(true);

	// Set Key Cap Mesh and Material Settings
	KeycapMesh->SetSkeletalMesh(InDataAsset->Mesh);
	if (nullptr != AnimInstanceClass)
	{
		KeycapMesh->SetAnimInstanceClass(AnimInstanceClass);
	}
	UMaterialInstanceDynamic* TextureMaterial = KeycapMesh->CreateAndSetMaterialInstanceDynamic(1);
	if (TextureMaterial != nullptr)
	{
		TextureMaterial->SetTextureParameterValue(FName("MainTex"), InDataAsset->Texture);
	}

	SetActorLabel(*GetCardInfo().Name);
}

void AJSCard::ActivateCardEffect(int32 InOrder)
{
	if (EffectComponent != nullptr)
	{
		EffectComponent->OnActivateEffect();
	}
}

int32 AJSCard::GetResultCarat()
{
	if (EffectComponent != nullptr)
	{
		return EffectComponent->GetEffectResult();
	}

	return 0;
}


void AJSCard::SetCardStateActive(bool InActive)
{
	if (!InActive && CardState == ECardState::Holding)
	{
		SetActorLocation(OriginPosition);
		return;
	}

	// Bind Delegate to GameState
	AJSGameState* const GameState = GetWorld()->GetGameState<AJSGameState>();
	if (nullptr != GameState)
	{
		if (InActive)
		{
			FVector SlotPos;
			if (CardState == ECardState::Holding)
			{
				// User is Holding Card, and Suceeded to Activate
				if (GameState->RegisterActivateCard(this, SlotNum, SlotPos))
				{
					CardState = ECardState::Activated;
					bIsActivated = true;
					SetActorLocation(FVector(SlotPos.X, SlotPos.Y, SlotPos.Z + 2.f));
				}
				// User is Holding Card, but failed to Activate
				else
				{
					SetActorLocation(OriginPosition);
				}
			}
			else if (CardState == ECardState::Activated)
			{
				if (SlotNum >= 0 && SlotNum <= 49)
				{
					{
						SetActorLocation(OriginPosition);
					}
				}
			}
		}
		else
		{
			GameState->UnregisterActivateCard(this);
			CardState = ECardState::Holding;
			bIsActivated = false;
		}
	}
}

bool AJSCard::OnSelectActor()
{
	if (CardState == ECardState::Inventory)
		return false;

	bIsGrabbed = true;
	OriginPosition = GetActorLocation();
	CaseMesh->BodyInstance.SetEnableGravity(false);

	return true;
}

void AJSCard::OnReleaseActor()
{
	UE_LOG(LogTemp, Log, TEXT("%d, %d"), bIsPlaceable, SlotNum);

	if(bIsPlaceable)
	{
		// Check If Card is on right place else go back to origin Place
		if (SlotNum >= 0)
		{
			SetCardStateActive(true);

		}
		else if (SlotNum == -2)
		{
			SetCardStateActive(false);

		}
	}
	else
	{
		SetActorLocation(OriginPosition);
	}
	
	bIsGrabbed = false;
	CaseMesh->BodyInstance.SetEnableGravity(true);
}

void AJSCard::OnMouseEnterActor()
{
	SetActiveCardInfoHUD(true);
}

void AJSCard::OnMouseExitActor()
{
	SetActiveCardInfoHUD(false);
}

void AJSCard::SetActiveCardInfoHUD(bool InActive) const
{
	AJSHUD* JSHud = Cast<AJSHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (JSHud != nullptr)
	{
		if (InActive)
		{
			FVector2D NewScreenPosition = FVector2D(0.f, 0.f);

			GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(GetActorLocation(), NewScreenPosition);
			JSHud->ShowCardInfoWidget(CardData, NewScreenPosition.X, NewScreenPosition.Y, true);
		}
		else
		{
			JSHud->ShowCardInfoWidget(CardData, 0.f, 0.f, false);
		}
	}
}

void AJSCard::SetOutlineColor(const FLinearColor InColor) const
{

}