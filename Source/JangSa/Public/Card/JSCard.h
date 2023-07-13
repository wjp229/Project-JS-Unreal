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

	void SetCardState(ECardState InState);

protected:
	int CardNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CardInfo)
	FCardInfoData CardData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CardRender)
	TObjectPtr<UStaticMeshComponent> CaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CardRender)
	TObjectPtr<USkeletalMeshComponent> KeycapMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CardCollider, meta=(AllowPrivateAccess))
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;
	
	UPROPERTY(VisibleAnywhere, Category=Effect)
	TObjectPtr<class UJSCardEffectComponent> EffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AnimationClass)
	TSubclassOf<class UJSCardAnimInstance> AnimInstanceClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ParticleEffect)
	TObjectPtr<class UParticleSystemComponent> ParticleEffectComponent;
	
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
	
	uint8 bIsPlaceable : 1;
	int32 SlotNum;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CardState", meta=(AllowPrivateAccess))
	ECardState CardState;

	FTimerHandle GravityTimerHandler;

private:
	FVector OriginPosition;
	FVector OriginScale;

public:
	uint8 bIsShaking : 1;
	uint8 bIsGrabbed : 1;
	uint8 bIsActivated : 1;

private:
	void ShakeMesh();
	void SetOutline(int32 InValue);

	FTimerHandle ShakeTimerHandler;
};
