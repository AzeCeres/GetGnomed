// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpawnPoint.h"
#include "GameFramework/Actor.h"
#include "WaveSpawner.generated.h"

UCLASS()
class GETGNOMED_API AWaveSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//UPROPERTY(EditAnywhere) The TArray is empty, and isn't serializeable. todo make it editable from blueprints
	TArray<AEnemySpawnPoint>* SpawnPoints;
	void SpawnWave(int NrOfEnemies, float TimeBetweenSpawns);
	bool isTimeBetweenIndividualSpawns;
private:
	int EnemiesToSpawn{0};
	void SpawnEnemy(int IndexOfSpawnPoints);
	float spawnBuffer{0};
	float spawnTimer{0};
	int currentSpawnPointIndex{0};
};
