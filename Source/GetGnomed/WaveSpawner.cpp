// Fill out your copyright notice in the Description page of Project Settings.
#include "WaveSpawner.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWaveSpawner::AWaveSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWaveSpawner::BeginPlay()
{
	SpawnPoints.Init(nullptr,3);
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnPoint::StaticClass(), SpawnPoints);
	SpawnWave(100,5);
}

// Called every frame
void AWaveSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	spawnTimer+=DeltaTime;
	if (spawnTimer < spawnBuffer || EnemiesToSpawn <= 0) return;
	
	if (isTimeBetweenIndividualSpawns)
	{
		SpawnEnemy(currentSpawnPointIndex);
		EnemiesToSpawn-=1;
		currentSpawnPointIndex +=1;
		if (currentSpawnPointIndex == SpawnPoints.Num())
		{
			currentSpawnPointIndex=0;
		}
		spawnTimer=0;
	}
	else
	{
		for (int i = 0; i < SpawnPoints.Num(); ++i)
		{
			if (EnemiesToSpawn<=0)
				break;
			SpawnEnemy(i);
			EnemiesToSpawn-=1;
		}
		spawnTimer=0;
	}
}

void AWaveSpawner::SpawnWave(int NrOfEnemies, float TimeBetweenSpawns)
{
	EnemiesToSpawn=NrOfEnemies;
	spawnBuffer = TimeBetweenSpawns;
	spawnTimer=0;
}

void AWaveSpawner::SpawnEnemy(int IndexOfSpawnPoints)
{
	Cast<AEnemySpawnPoint>(SpawnPoints[IndexOfSpawnPoints])->SpawnEnemy();
}



