// Fill out your copyright notice in the Description page of Project Settings.


#include "JSGameMode.h"

#include "JSGameState.h"
#include "JSHUD.h"
#include "JSPlayerController.h"
#include "JSSpectatorPawn.h"

AJSGameMode::AJSGameMode()
{
	DefaultPawnClass = AJSSpectatorPawn::StaticClass();
	HUDClass = AJSHUD::StaticClass();
	PlayerControllerClass = AJSPlayerController::StaticClass();
	GameStateClass = AJSGameState::StaticClass();
}

void AJSGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Cast<AJSGameState>(GameState)->NotifyAddRemainCardTurn.AddDynamic(this, &AJSGameMode::TestBinding);

}

void AJSGameMode::TestBinding(int32 num)
{
	UE_LOG(LogTemp, Log, TEXT("HIHIHIHIIHIHIH"));
}
