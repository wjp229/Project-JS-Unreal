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