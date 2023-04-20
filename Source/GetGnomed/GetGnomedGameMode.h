// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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

private:
	void TriggerWin();
};

