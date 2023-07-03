// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCard.h"

#include "JSCardAnimInstance.h"
#include "Card/JSCardEffectComponent.h"
#include "JSGameState.h"
#include "Animation/AnimInstance.h"
#include "Data/JSCardDataAsset.h"
#include "Kismet/GameplayStatics.h"
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

	RemainTurn = GetCardInfo().InitRemainTurn;
	CardState = ECardState::Inventory;

	DefaultOutlineColor = FLinearColor(1.0f, 1.0f, 1.0f);
	MouseEnterOutlineColor = FLinearColor(0.1f, 1.0f, 0.1f);
	DisabledOutlineColor = FLinearColor(1.0f, 0.1f, 0.1f);
	SelectOulineColor = FLinearColor(1.0f, 1.0f, 0.1f);
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

	if (nullptr == InDataAsset)
	{
		UE_LOG(LogTemp, Log, TEXT("Null Data Asset "));
		return;
	}

	UJSCardEffectComponent* CardEffectComponent = NewObject<UJSCardEffectComponent>(this, InDataAsset->EffectComponent);
	EffectComponent = CardEffectComponent;
	EffectComponent->RegisterComponent();

	KeycapMesh->SetSkeletalMesh(InDataAsset->Mesh);
	CaseMesh->SetSimulatePhysics(true);

	if (nullptr != AnimInstanceClass)
	{
		KeycapMesh->SetAnimInstanceClass(AnimInstanceClass);
	}

	UMaterialInstanceDynamic* TextureMaterial = KeycapMesh->CreateAndSetMaterialInstanceDynamic(1);
	if (TextureMaterial != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("SetTexture %s"), *InDataAsset->Texture->GetName());
		TextureMaterial->SetTextureParameterValue(FName("MainTex"), InDataAsset->Texture);
	}
	
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
	if (!Active && CardState == ECardState::Holding)
	{
		return;
	}

	// Bind Delegate to GameState
	AJSGameState* const GameState = GetWorld()->GetGameState<AJSGameState>();
	if (nullptr != GameState)
	{
		if (Active)
		{
			FVector SlotPos;
			// To do : Set Slot Num
			if (GameState->RegisterActivateCard(this, SlotNum, SlotPos))
			{
				CardState = ECardState::Activated;
				bIsActivated = true;
				SetActorLocation(FVector(SlotPos.X, SlotPos.Y, SlotPos.Z + 2.f));
			}
			else
			{
				SetActorLocation(OriginPosition);
			}
		}
		else
		{
			GameState->UnregisterActivateCard(this, SlotNum);
			CardState = ECardState::Holding;
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
	SetOutlineColor(SelectOulineColor);

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
	bIsGrabbed = false;

	UE_LOG(LogTemp, Log, TEXT("Release Card"));

	CaseMesh->BodyInstance.SetEnableGravity(true);
	SetOutlineColor(DefaultOutlineColor);
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

void AJSCard::SetPossessCard(bool IsPossessed)
{
	bIsSelected = IsPossessed;

	// OutLine Color to Color Green
}

void AJSCard::SetOutlineColor(const FLinearColor InColor) const
{
	// int32 Index = KeycapMesh->GetMaterialIndex(TEXT("Mat_Outline"));
	// UMaterialInstanceDynamic* OutlineMaterial = KeycapMesh->CreateDynamicMaterialInstance(Index);
	// if(OutlineMaterial != nullptr)
	// {
	// 	UE_LOG(LogTemp, Log, TEXT("Change Outline Mat %s"), *InColor.ToString());
	// 	OutlineMaterial->SetVectorParameterValue(TEXT("OutlineColor"), InColor);
	//
	// 	FHashedMaterialParameterInfo Info;
	// 	
	// 	UE_LOG(LogTemp, Log, TEXT("Change Outline Mat %s"), OutlineMaterial->GetVectorParameterValue());
	//
	// }
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
}
