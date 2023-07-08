// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/JSTurnEventManager.h"

#include "JSGameState.h"
#include "Data/JSEventData.h"
#include "Event/JSEventAction.h"
#include "GameFramework/PlayerController.h"
#include "UI/JSHUD.h"

void AJSTurnEventManager::BeginPlay()
{
	Super::BeginPlay();

	AJSGameState* GameState = Cast<AJSGameState>(GetWorld()->GetGameState());
	if(GameState != nullptr)
	{
		GameState->NotifyCheckEvent.AddDynamic(this, &AJSTurnEventManager::SpawnCurrentStageEvents);
	}
}

void AJSTurnEventManager::SpawnCurrentStageEvents(int32 InStageNum)
{
	// Stack Current Event Actions
	if (CurrentStageEvents.Num() > 0)
	{
		CurrentStageEvents.Empty();
	}

	TArray<UJSEventData*> CurrentStageData;
	auto IsValidStageNum = [InStageNum](UJSEventData* Value) { return Value->StageNum == InStageNum; };
	auto GetCurrentStageData = [](UJSEventData* Value) { return Value; };

	Algo::TransformIf(EventActions, CurrentStageData, IsValidStageNum, GetCurrentStageData);

	for (int i = 0; i < CurrentStageData.Num(); i++)
	{
		float RandVal = FMath::RandRange(0.f, 1.f);

		if (RandVal < CurrentStageData[i]->Probability)
		{
			CurrentStageEvents.Add(CurrentStageData[i]);
		}
	}
	
	// Call
	CallNextEvent();
}

void AJSTurnEventManager::CallNextEvent()
{
	if (CurrentStageEvents.Num() <= 0)
	{
		AJSGameState* GameState = Cast<AJSGameState>(GetWorld()->GetGameState());
		if(GameState != nullptr)
		{
			AJSHUD* JSHud = Cast<AJSHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			if(JSHud != nullptr)
			{
				JSHud->CloseEventInfoWidget();
			}
			
			GameState->OnResetShop();
		}
		
		return;
	}

	// Init JS Event 
	UJSEventData* EventData = CurrentStageEvents.Pop();

	AJSHUD* JSHud = Cast<AJSHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(JSHud != nullptr)
	{
		JSHud->ShowEventInfoWidget(EventData);
	}
}