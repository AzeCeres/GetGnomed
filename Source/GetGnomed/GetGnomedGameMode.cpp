// Copyright Epic Games, Inc. All Rights Reserved.

#include "GetGnomedGameMode.h"
#include "GetGnomedCharacter.h"
#include "Kismet/GameplayStatics.h"
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
	if (GetOptions()=="?true"){
		isNight = true;
	}
}

void AGetGnomedGameMode::Tick(float DeltaTime)
{
	while (GameRunState)
	{
		GameTimeScore++;
	}
}

void AGetGnomedGameMode::StartGame()
{
	GameRunState = true;
	WaveSpawner.Init(nullptr, 0);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaveSpawner::StaticClass(), WaveSpawner);
	WaveController.Init(nullptr, 0);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaveController::StaticClass(), WaveController);
	
}

FString AGetGnomedGameMode::GetOptions()
{
	return OptionsString;
}

FString AGetGnomedGameMode::ParseOption(const FString& OptionString, const FString& OptionName)
{
	return ParseOption(OptionString,OptionName);
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
