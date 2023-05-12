// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveSpawner.h"
#include "WaveController.generated.h"

class AGetGnomedCharacter;

UCLASS()
class GETGNOMED_API AWaveController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	
	
	
	// functions
	UFUNCTION(BlueprintCallable, Category = Wave)
	int GetWave();
	UFUNCTION(BlueprintCallable, Category = Wave)
	void SetWave(int NewWaveID);
	UFUNCTION(BlueprintCallable, Category = Wave)
	int GetEnemyCount();

	UPROPERTY(EditAnywhere, Category=Wave)
	int EnemiesPerWave{15};
	
	UFUNCTION(BlueprintCallable, Category = "My Functions")
		void ControlWave(int EnemyWorth);
private:
	UFUNCTION(BlueprintCallable, Category = "My Functions")
		void ChangeWave(int WaveNR);
	// variables
	int WaveID;
	int EnemyCount;
	int TotScore;
	AActor* WaveSpawner;

	float e {2.71828};
	float multiplier{4};
	float minTime {2};
};
