// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveController.h"
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
}

// Called every frame
void AWaveController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveController::ControlWave()
{
	EnemyCount--;
	if(EnemyCount <=0 && WaveID < 4)
	{
		EnemyCount = (WaveID + 1) * 15;
		ChangeWave(WaveID + 1);
	}
}

void AWaveController::ChangeWave(int NewWave)
{
	WaveID++;
	Cast<AWaveSpawner>(WaveSpawner)->SpawnWave(NewWave * 15, 5 - NewWave);
	UE_LOG(LogTemp, Warning, TEXT("Spawning new wave"));
}