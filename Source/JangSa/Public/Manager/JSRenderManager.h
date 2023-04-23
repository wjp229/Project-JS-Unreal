// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CardInfoRowBase.h"
#include "Interfaces/JSCardRenderInterface.h"
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
	
	void CreateCardComponent();
	void SpawnCardRenderer(int32 InCardObjId);
	void DespawnCardRenderer(int32 InCardObjId);
	void UpdateCardInfo(int32 InCardObjId, FCardInfoData InCardData);

private:
	UPROPERTY()
	TMap<int32, TObjectPtr<IJSCardRenderInterface>> CardRenders;
	
};
