// Copyright Epic Games, Inc. All Rights Reserved.

#include "TD1GameMode.h"
#include "TD1PlayerController.h"
#include "TD1Character.h"
#include "UObject/ConstructorHelpers.h"

ATD1GameMode::ATD1GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATD1PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}