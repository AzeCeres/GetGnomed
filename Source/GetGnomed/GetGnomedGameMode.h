// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WaveController.h"
#include "WaveSpawner.h"
#include "GetGnomedGameMode.generated.h"

UCLASS(minimalapi)
class AGetGnomedGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGetGnomedGameMode();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		bool ControllerWinBool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		bool GameRunState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float GameScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float GameTimeScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TArray<AActor*> WaveController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TArray<AActor*> WaveSpawner;

	UFUNCTION(BlueprintCallable, Category = "My Functions")
		void StartGame();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="My Functions")
	virtual FString GetOptions();

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	virtual FString ParseOption(const FString& OptionString, const FString& OptionName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	bool isNight{false};
private:
	void TriggerWin();
};

