// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GetGnomedCharacter.h"
#include "GetGnomedGameMode.h"

#include "SpeedPickup.generated.h"

class USphereComponent;
UCLASS()
class GETGNOMED_API ASpeedPickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpeedPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EffectStuffs)
		bool SpeedEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EffectStuffs)
		int SpeedDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EffectStuffs)
		int MaxSpeedDuration = 5;

	// Functions

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void DestroySpeedUp();

	UFUNCTION()
		void DisableSpeedUp();
};
