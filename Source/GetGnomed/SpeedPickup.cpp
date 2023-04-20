// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedPickup.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"


// Sets default values
ASpeedPickup::ASpeedPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitSphereRadius(10.f);
	//Collider->OnComponentBeginOverlap.AddDynamic(this, &AE_Bullet::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

}

// Called when the game starts or when spawned
void ASpeedPickup::BeginPlay()
{
	Super::BeginPlay();
	SpeedEffect = false;
	SpeedDuration = 0;
}

/*
 void AGetGnomedCharacter::IncreaseSpeed()
{

		MovementSpeed = 1.5;
		//wait for set time
		MovementSpeed = 1;
		//Call destructor for pickup item
	}
}
*/

// Called every frame
void ASpeedPickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (SpeedEffect)
	{
		SpeedDuration += DeltaSeconds;
		if (SpeedDuration >= MaxSpeedDuration)
		{
			SpeedEffect = false;
			DisableSpeedUp();
			SpeedDuration = 0;
		}
	}
}

void ASpeedPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Speed up triggered"));
	if (OtherActor->IsA<AGetGnomedCharacter>() && !SpeedEffect) {
		SpeedEffect = true;
		Cast<AGetGnomedCharacter>(OtherActor)->IncreaseSpeed(10);
	}
}

void ASpeedPickup::DestroySpeedUp()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

/*void ASpeedPickup::DisableSpeedUp()
{
	AGetGnomedCharacter* PlayerCharacter = FindObject<AGetGnomedCharacter>(ANY_PACKAGE, TEXT("AGetGnomedCharacter"));
	PlayerCharacter->IncreaseSpeed(1);
}*/

