// Copyright Epic Games, Inc. All Rights Reserved.

#include "TD1PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TD1Character.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ATD1PlayerController::ATD1PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ATD1PlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATD1PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATD1PlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATD1PlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATD1PlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATD1PlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ATD1PlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ATD1PlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ATD1PlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ATD1PlayerController::OnTouchReleased);
	}
}

void ATD1PlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ATD1PlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ATD1PlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ATD1PlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ATD1PlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
