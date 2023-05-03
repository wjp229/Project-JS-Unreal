// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/JSRenderManager.h"
#include "Card/JSCardPaperRenderer.h"
#include "Card/JSCardStoneRenderer.h"

UJSRenderManager::UJSRenderManager()
{
}

void UJSRenderManager::SpawnCardRenderer(const int32 InCardObjId, const ECardRenderState InCardState,
                                         const FCardInfoData& InCardData)
{
	UObject* NewCardRenderer = nullptr;

	switch (InCardState)
	{
	case ECardRenderState::UMG:
		UE_LOG(LogTemp, Log, TEXT("Not Made Yet"));
		break;
	case ECardRenderState::Paper:
		UE_LOG(LogTemp, Log, TEXT("Paper Version Card has made!!"));
		NewCardRenderer = NewObject<AJSCardPaperRenderer>(GetWorld(), AJSCardPaperRenderer::StaticClass());
		break;
	case ECardRenderState::Stone:
		UE_LOG(LogTemp, Log, TEXT("Stone Version Card has made!!"));
		NewCardRenderer = NewObject<AJSCardStoneRenderer>(GetWorld(), AJSCardStoneRenderer::StaticClass());
		break;
	default:
		break;
	}

	if (NewCardRenderer != nullptr)
		CardRenders.Add(InCardObjId, Cast<IJSCardRenderInterface>(NewCardRenderer));

	UpdateCardInfo(InCardObjId, InCardData);
}

void UJSRenderManager::DespawnCardRenderer(const int32 InCardObjId)
{
	CardRenders.Remove(InCardObjId);
}

void UJSRenderManager::UpdateCardInfo(const int32 InCardObjId, const FCardInfoData& InCardData)
{
	TObjectPtr<IJSCardRenderInterface> Interface = CardRenders.FindRef(InCardObjId);

	if(Interface == nullptr)
	{
		Interface->UpdateCardInfo(InCardData);
	}
}
