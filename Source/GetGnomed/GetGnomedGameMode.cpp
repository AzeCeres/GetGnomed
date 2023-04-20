// Copyright Epic Games, Inc. All Rights Reserved.

#include "GetGnomedGameMode.h"
#include "GetGnomedCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGetGnomedGameMode::AGetGnomedGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PrimaryActorTick.bCanEverTick = true;

	GameRunState = false;
	ControllerWinBool = false;
}

void AGetGnomedGameMode::Tick(float DeltaTime)
{
	while (GameRunState)
	{
		GameTimeScore++;
	}

	//wave controller stuff, eg. check for enemy count and spawn waves accordingly
}

void AGetGnomedGameMode::TriggerWin()
{
	if (ControllerWinBool)
	{
		//show result of win
		UE_LOG(LogTemp, Warning, TEXT("You Win!"));
	}
	else
	{
		//show result of loss
		UE_LOG(LogTemp, Warning, TEXT("You Lose!"));
	}

	GameRunState = false;
	//save GameTimeScore and GameScore
}
