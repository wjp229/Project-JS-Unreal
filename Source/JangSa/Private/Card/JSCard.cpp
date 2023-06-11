// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCard.h"
#include "Card/JSCardEffectComponent.h"
#include "JSGameState.h"
#include "Data/JSCardDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "UI/JSHUD.h"
#include "UObject/ConstructorHelpers.h"

AJSCard::AJSCard()
{
	CaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Case Mesh"));
	KeycapMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Keycap Mesh"));

	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		CaseMeshRef(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (CaseMeshRef.Succeeded())
	{
		CaseMesh->SetStaticMesh(CaseMeshRef.Object);
	}

	RootComponent = CaseMesh;
	CaseMesh->SetRelativeScale3D(FVector(.05f, .05f, .01f));
	CaseMesh->SetSimulatePhysics(true);

	KeycapMesh->SetupAttachment(CaseMesh);
	KeycapMesh->SetRelativeScale3D(FVector(.7f, .7f, 3.5f));
	KeycapMesh->SetRelativeRotation(FRotator(.0f, 270.0f, 0.f));
	KeycapMesh->SetRelativeLocation(FVector(.0f, .0f, 50.f));
	KeycapMesh->SetSimulatePhysics(false);

	RemainTurn = GetCardInfo().InitRemainTurn;
	InfoShowDelayTime = .7f;
	bIsShowingInfo = false;
	bIsDetected = false;
	CardState = ECardState::Holding;
}

void AJSCard::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bIsDetected || bIsShowingInfo) return;

	CurrentDetectingTime += DeltaSeconds;

	if (CurrentDetectingTime > InfoShowDelayTime)
	{
		bIsShowingInfo = true;
		SetActiveCardInfoHUD(true);
	}
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

	CaseMesh->BodyInstance.SetEnableGravity(false);

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

	CaseMesh->BodyInstance.SetEnableGravity(true);
}

void AJSCard::OnMouseEnterActor()
{
	// To do : Activate Info HUD After few seconds
	UE_LOG(LogTemp, Log, TEXT("Mouse Enter %s"), *GetActorNameOrLabel());
	bIsDetected = true;
}

void AJSCard::OnMouseExitActor()
{
	// To do : Deactivate Info HUD After few Seconds
	UE_LOG(LogTemp, Log, TEXT("Mouse Exit %s"), *GetActorNameOrLabel());

	bIsDetected = false;
	CurrentDetectingTime = 0.f;
	bIsShowingInfo = false;

	SetActiveCardInfoHUD(false);
}

void AJSCard::SetActiveCardInfoHUD(bool InActive)
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
