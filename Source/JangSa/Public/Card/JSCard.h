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
	void InitCard(const FCardInfoData& InCardData, int32 InObjectID, class UJSCardEffectComponent* InEffectComponent);


protected:
	UFUNCTION()
	void OnDestroyCard();

	int CardNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=CardInfo)
	FCardInfoData CardData;

	UPROPERTY()
	int32 CardObjID;

	UPROPERTY(EditAnywhere, Category=CardRender)
	TObjectPtr<UStaticMeshComponent> KeycapMesh;

	UPROPERTY(VisibleAnywhere, Category=Effect)
	TObjectPtr<UJSCardEffectComponent> EffectComponent;

	int32 RemainTurn;

	// Card Activating Effect Section
public:
	UFUNCTION()
	virtual void ActivateCardEffect(int32 InOrder) override;

	UFUNCTION()
	void AddRemainTurn(int32 Value);

	virtual void SetCardStateActive(bool Active);

	// Mouse Interaction with actor
	virtual bool OnSelectActor() override;
	virtual void OnReleaseActor() override;

	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;
	virtual void OnMouseEnterActor() override;
	virtual void OnMouseExitActor() override;

	void ActivateCardInfoHUD();


	void SetPossessCard(bool IsPossessed);

	ECardState CardState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Placeable");
	uint8 bIsPlaceable : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slot");
	int32 SlotNum;

private:
	UPROPERTY(VisibleAnywhere, Category="Interaction")
	uint8 bIsSelected;

	FVector OriginPosition;

	// Card Cursor Overlap Section
public:
private:
	float InfoShowDelayTime = 2.0f;
	FTimerHandle CardInfoTimerHandler;
};
