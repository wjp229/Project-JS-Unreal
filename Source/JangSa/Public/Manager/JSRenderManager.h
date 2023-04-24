// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CardInfoRowBase.h"
#include "Interfaces/JSCardRenderInterface.h"
#include "JSTypes.h"
#include "UObject/NoExportTypes.h"
#include "JSRenderManager.generated.h"

/**
 * 
 */
UCLASS()
class JANGSA_API UJSRenderManager : public UObject
{
	GENERATED_BODY()

public:
	UJSRenderManager();
	
	void SpawnCardRenderer(const int32 InCardObjId, const ECardRenderState InCardState,
											 const FCardInfoData& InCardData);
	void DespawnCardRenderer(const int32 InCardObjId);
	void UpdateCardInfo(const int32 InCardObjId, const FCardInfoData& InCardData);

private:
	UPROPERTY()
	TMap<int32, TObjectPtr<IJSCardRenderInterface>> CardRenders;
};
