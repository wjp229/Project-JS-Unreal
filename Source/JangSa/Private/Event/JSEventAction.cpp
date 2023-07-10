// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/JSEventAction.h"

#include "JSGameState.h"
#include "Manager/JSTurnEventManager.h"

void UJSEventAction::InitializeEvent()
{
}

void UJSEventAction::ActivateEvent_Implementation()
{
	AJSGameState* GameState = Cast<AJSGameState>(GetOuter()->GetWorld()->GetGameState());

	if(nullptr != GameState)
	{
		GameState->GetTurnManager()->CallNextEvent();
	}
}
