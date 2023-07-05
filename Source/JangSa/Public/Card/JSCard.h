// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/JSTypes.h"
#include "Data/CardInfoRowBase.h"
#include "Interfaces/CardEffectInterface.h"
#include "Interfaces/JSInputInterface.h"
#include "JSCard.generated.h"

UCLASS()
class JANGSA_API AJSCard : public AActor, public IJSCardEffectInterface, public IJSInputInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJSCard();

	FCardInfoData GetCardInfo() const;
	void InitCard(const FCardInfoData& InCardData, int32 InObjectID, class UJSCardDataAsset* InDataAsset);

protected:
	int CardNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CardInfo)
	FCardInfoData CardData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CardRender)
	TObjectPtr<UStaticMeshComponent> CaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CardRender)
	TObjectPtr<USkeletalMeshComponent> KeycapMesh;

	UPROPERTY(VisibleAnywhere, Category=Effect)
	TObjectPtr<class UJSCardEffectComponent> EffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AnimationClass)
	TSubclassOf<class UJSCardAnimInstance> AnimInstanceClass;
	
	// Card Activating Effect Section
public:
	UFUNCTION()
	virtual void ActivateCardEffect(int32 InOrder) override;

	UFUNCTION()
	virtual int32 GetResultCarat() override;

	virtual void SetCardStateActive(bool InActive);

	// Mouse Interaction with actor
	virtual bool OnSelectActor() override;
	virtual void OnReleaseActor() override;

	virtual void OnMouseEnterActor() override;
	virtual void OnMouseExitActor() override;

	void SetActiveCardInfoHUD(bool InActive) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CardState")
	ECardState CardState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Placeable");
	uint8 bIsPlaceable : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot");
	int32 SlotNum;

private:
	FVector OriginPosition;
	
	// Outline Color Section
private:
	void SetOutlineColor(const FLinearColor InColor) const;

	FLinearColor DefaultOutlineColor;
	FLinearColor MouseEnterOutlineColor;
	FLinearColor SelectOulineColor;
	FLinearColor DisabledOutlineColor;

public:
	uint8 bIsGrabbed : 1;
	uint8 bIsActivated : 1;
};
