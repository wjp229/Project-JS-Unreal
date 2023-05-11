// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/JSSpectatorPawn.h"
#include "JSGameMode.h"
#include "Player/JSCameraComponent.h"
#include "Player/JSPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "JSControlData.h"
#include "Engine/LocalPlayer.h"

AJSSpectatorPawn::AJSSpectatorPawn(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bAddDefaultMovementBindings = false;
	JsCameraComponent = CreateDefaultSubobject<UJSCameraComponent>(TEXT("Camera"));

	static ConstructorHelpers::FObjectFinder<UJSControlData> ControlDataRef(TEXT("/Script/JangSa.JSControlData'/Game/CameraData/DA_JSController.DA_JSController'"));
	if(ControlDataRef.Succeeded())
	{
	 	ControlData = ControlDataRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionClickRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IJS_Click.IJS_Click'"));
	if(InputActionClickRef.Succeeded())
	{
		ClickAction = InputActionClickRef.Object;
	}
	// Set CameraRot
}

void AJSSpectatorPawn::BeginPlay()
{
	Super::BeginPlay();

	SetMappingContext();
}

void AJSSpectatorPawn::SetMappingContext()
{
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		if(nullptr != ControlData)
		{
			Subsystem->AddMappingContext(ControlData->InputMappingContext, 0);
		}
	}
}

void AJSSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	AJSPlayerController* PlayerController = CastChecked<AJSPlayerController>(GetController());

	UE_LOG(LogTemp, Log, TEXT("Setup"));

	
	EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &AJSSpectatorPawn::Test);
}

void AJSSpectatorPawn::Test()
{
	UE_LOG(LogTemp, Log, TEXT("TEST!!"));
}
