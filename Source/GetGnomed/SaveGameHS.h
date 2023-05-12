// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameHS.generated.h"

/**
 * 
 */
UCLASS()
class GETGNOMED_API USaveGameHS : public USaveGame
{
	GENERATED_BODY()


public:

	USaveGameHS();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Highscore")
		int HighScore;
};
