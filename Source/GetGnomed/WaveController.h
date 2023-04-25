// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveSpawner.h"
#include "WaveController.generated.h"

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
	// variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		int WaveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		int EnemyCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		AActor* WaveSpawner;

	// functions

	UFUNCTION(BlueprintCallable, Category = "My Functions")
		void ControlWave();

	UFUNCTION(BlueprintCallable, Category = "My Functions")
		void ChangeWave(int NewWave);
};
