// Fill out your copyright notice in the Description page of Project Settings.


#include "JSGameMode.h"
#include "JSGameState.h"
#include "Pawns/JSSpectatorPawn.h"
#include "Player/JSPlayerController.h"
#include "UI/JSHUD.h"

AJSGameMode::AJSGameMode()
{
	DefaultPawnClass = AJSSpectatorPawn::StaticClass();
	HUDClass = AJSHUD::StaticClass();
	PlayerControllerClass = AJSPlayerController::StaticClass();
	GameStateClass = AJSGameState::StaticClass();
	SpectatorClass = AJSSpectatorPawn::StaticClass();
}
