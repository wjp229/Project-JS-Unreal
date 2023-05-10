// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CardInfoRowBase.h"
#include "Interfaces/CardEffectInterface.h"
#include "JSCard.generated.h"

UCLASS()
class JANGSA_API AJSCard : public AActor, public ICardEffectInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AJSCard();

	FCardInfoData GetCardInfo() const;
	void InitCard(const FCardInfoData& InCardData, int32 InObjectID, class UJSCardEffectComponent* InEffectComponent);

	virtual void OnActivateCardEffect(int32 InOrder) override;

	//void SetEffectComponent()
	
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
	
};