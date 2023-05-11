// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveController.h"

#include <Imath/Deploy/Imath-3.1.3/include/Imath/ImathMath.h>

#include "GetGnomedCharacter.h"
#include "WaveSpawner.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWaveController::AWaveController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveController::BeginPlay()
{
	Super::BeginPlay();

	WaveID = 0;
	EnemyCount = 0;

	WaveSpawner = UGameplayStatics::GetActorOfClass(GetWorld(), AWaveSpawner::StaticClass());
	ChangeWave(WaveID);
}

// Called every frame
void AWaveController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AWaveController::GetWave()
{
	return WaveID;
}

void AWaveController::SetWave(int NewWaveID)
{
	WaveID = NewWaveID;
}

int AWaveController::GetEnemyCount()
{
	return EnemyCount;
}

void AWaveController::ControlWave()
{
	EnemyCount--;
	if(EnemyCount <=0)
	{
		ChangeWave(WaveID);
	}
}

void AWaveController::ChangeWave(int WaveNR)
{
	WaveID = WaveNR + 1;

	if (WaveID == 11)
	{
		ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (character == nullptr) return;

		AGetGnomedCharacter* player = Cast<AGetGnomedCharacter>(character);
		if (player == nullptr) return;

		player->EndGame();
	}

	EnemyCount = pow(e,0.2*WaveID)*4+1;
	
	//EnemyCount = WaveID * EnemiesPerWave;
	float TimeBetweenSpawns = pow(e, -0.05*WaveID) * multiplier + minTime;
	Cast<AWaveSpawner>(WaveSpawner)->SpawnWave(EnemyCount, TimeBetweenSpawns);
	//if(GEngine)GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Wave Nr %i, Time Between Spawns %f Enemy Count %i"), WaveID, TimeBetweenSpawns, EnemyCount));
}