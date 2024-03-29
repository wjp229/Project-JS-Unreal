// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/JSCardSlot.h"
#include "Card/JSCard.h"
#include "Engine/TriggerBox.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AJSCardSlot::AJSCardSlot()
{
	SlotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeycapMesh"));
	TriggerBox = CreateDefaultSubobject<ATriggerBox>(TEXT("TriggerBox"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SlotMeshRef(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if(SlotMeshRef.Succeeded())
	{
		SlotMesh->SetStaticMesh(SlotMeshRef.Object);
	}

	RootComponent = SlotMesh;

	FVector MeshSize(0.07f, 0.07f, 0.01f);
	SlotMesh->SetRelativeScale3D(MeshSize);
	SlotMesh->SetCollisionProfileName(FName(TEXT("PlaceableActor")));
}

void AJSCardSlot::InitSlot(int32 InSlotNum)
{
	TriggerBox = Cast<ATriggerBox>(GetWorld()->SpawnActor(ATriggerBox::StaticClass()));

	FVector TriggerSpawnLocation = GetActorLocation() +  FVector(0.f,0.f,7.f) ;
	FVector TriggerBoxScale = FVector(0.08f,0.08f,0.15f);
	
	TriggerBox->SetActorLocation(TriggerSpawnLocation);
	TriggerBox->SetActorScale3D(TriggerBoxScale);

	TriggerBox->OnActorBeginOverlap.AddDynamic(this, &AJSCardSlot::OnCardBeginOverlap);
	TriggerBox->OnActorEndOverlap.AddDynamic(this, &AJSCardSlot::OnCardEndOverlap);
	
	SlotNum = InSlotNum;

}

void AJSCardSlot::RegisterCard()
{
	SlotMesh->SetCustomDepthStencilValue(0);
}

void AJSCardSlot::OnCardBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{	
	AJSCard* InCard = Cast<AJSCard>(OtherActor);
	if(nullptr != InCard)
	{
		InCard->SlotNum = SlotNum;
		InCard->bIsPlaceable = true;

		SlotMesh->SetCustomDepthStencilValue(253);
	}
}

void AJSCardSlot::OnCardEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	AJSCard* InCard = Cast<AJSCard>(OtherActor);
	if(nullptr != InCard)
	{
		UE_LOG(LogTemp, Log, TEXT("AJSCardSlot bIsPlaceable: %d"), InCard->bIsPlaceable);
		UE_LOG(LogTemp, Log, TEXT("AJSCardSlot SlotNum: %d"), InCard-> SlotNum);

		if(InCard->SlotNum == SlotNum)
		{
			InCard->SlotNum = -1;
			InCard->bIsPlaceable = false;
		}
		
		SlotMesh->SetCustomDepthStencilValue(0);
	}
}


