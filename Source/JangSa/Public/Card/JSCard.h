// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JSTypes.h"
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
	int CardNum;

	UPROPERTY(VisibleAnywhere, Category=CardInfo)
	FCardInfoData CardData;
	int32 RemainTurn;

	UPROPERTY()
	int32 CardObjID;

	UPROPERTY(VisibleAnywhere, Category=CardRender)
	TObjectPtr<UStaticMeshComponent> KeycapMesh;

	UPROPERTY(VisibleAnywhere, Category=Effect)
	TObjectPtr<UJSCardEffectComponent> EffectComponent;

	UFUNCTION()
	void AddRemainTurn(int32 Value);
	UFUNCTION()
	void OnDestroyCard();

public:
	UFUNCTION()
	virtual void OnActivateCardEffect(int32 InOrder) override;

	virtual bool OnSelectActor() override;
	virtual void OnReleaseActor() override;
	
	void SetPossessCard(bool isPossessed);

	ECardState CardState;

private:
	UPROPERTY(VisibleAnywhere, Category="Interaction")
	uint8 bIsSelected;
};
