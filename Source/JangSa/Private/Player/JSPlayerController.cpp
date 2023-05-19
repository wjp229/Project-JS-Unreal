// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/JSPlayerController.h"
#include "JSGameState.h"
#include "Player/JSInput.h"
#include "UObject/ConstructorHelpers.h"
#include "JSControlData.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"
#include "Interfaces/JSInputInterface.h"

AJSPlayerController::AJSPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;

	static ConstructorHelpers::FObjectFinder<UJSControlData> ControlDataRef(TEXT("/Script/JangSa.JSControlData'/Game/CameraData/DA_JSController.DA_JSController'"));
	if(ControlDataRef.Succeeded())
	{
		ControlData = ControlDataRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionClickRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IJS_Click.IJS_Click'"));
	if(InputActionClickRef.Succeeded())
	{
		PressAction = InputActionClickRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionReleaseRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IJS_Release.IJS_Release'"));
	if(InputActionReleaseRef.Succeeded())
	{
		ReleaseAction = InputActionReleaseRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionDragRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IJS_Drag.IJS_Drag'"));
	if(InputActionDragRef.Succeeded())
	{
		DragAction = InputActionDragRef.Object;
	}
}

void AJSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	SetMappingContext();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(PressAction, ETriggerEvent::Triggered, this, &AJSPlayerController::OnTapPressed);
	EnhancedInputComponent->BindAction(ReleaseAction, ETriggerEvent::Completed, this, &AJSPlayerController::OnTapReleased);
	EnhancedInputComponent->BindAction(DragAction, ETriggerEvent::Triggered, this, &AJSPlayerController::OnDrag);
}

void AJSPlayerController::OnTapPressed()
{
	UE_LOG(LogTemp, Log, TEXT("On Tap Pressed"));
	
	const FVector2d CurrentMousePosition = GetCurrentMousePosition();
	GetHitActor(CurrentMousePosition);
}

void AJSPlayerController::OnTapReleased()
{
	UE_LOG(LogTemp, Log, TEXT("On Tap Released"));
	
	IJSInputInterface* InputInterface = Cast<IJSInputInterface>(SelectedObject);
	if(nullptr != InputInterface)
	{
		InputInterface->OnReleaseActor();
		SelectedObject = nullptr;
	}
}

AActor* AJSPlayerController::GetHitActor(const FVector2d& ScreenPosition)
{
	FHitResult Hit;
	
	if (GetHitResultAtScreenPosition(ScreenPosition, ECC_Visibility, true, Hit))
	{
		IJSInputInterface* InputInterface = Cast<IJSInputInterface>(Hit.GetActor());
		
		if(nullptr == InputInterface)
		{
			return nullptr;
		}
		
		if(!InputInterface->OnSelectActor())
			return nullptr;
		
		SelectedObject = Hit.GetActor();

		return SelectedObject;
	}

	return nullptr;
}

void AJSPlayerController::OnDrag()
{
	if(SelectedObject == nullptr)
	{
		return;
	}
	
	const FVector2d CurrentMousePosition = GetCurrentMousePosition();

	FHitResult Hit;
	
	if (GetHitResultAtScreenPosition(CurrentMousePosition, ECC_GameTraceChannel2, false, Hit))
	{
		FVector OffsetVector = FVector(.0f, .0f, 5.0f);
		
		SelectedObject->SetActorLocation(Hit.Location + OffsetVector);
	}
}

void AJSPlayerController::SetMappingContext() const
{
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		if(nullptr != ControlData)
		{
			Subsystem->AddMappingContext(ControlData->InputMappingContext, 0);
		}
	}
}

FVector2d AJSPlayerController::GetCurrentMousePosition()
{
	float MouseLocationX = 0;
	float MouseLocationY = 0;
	
	GetMousePosition(MouseLocationX, MouseLocationY);

	FVector2d NewPositionVector = FVector2d(MouseLocationX, MouseLocationY);
	
	return NewPositionVector;
}
