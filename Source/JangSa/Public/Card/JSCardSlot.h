// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JSCardSlot.generated.h"

UCLASS()
class JANGSA_API AJSCardSlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJSCardSlot();

	void InitSlot(int32 InSlotNum);

private:
	UFUNCTION()
	void OnCardBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnCardEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	int32 SlotNum;
	TObjectPtr<UStaticMeshComponent> SlotMesh;
	TObjectPtr<class ATriggerBox> TriggerBox;
};
