// Copyright Epic Games, Inc. All Rights Reserved.
// Edited and added onto by Julian
#include "GetGnomedCharacter.h"
#include "GetGnomedProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UnrealWidgetFwd.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


//////////////////////////////////////////////////////////////////////////
// AGetGnomedCharacter

AGetGnomedCharacter::AGetGnomedCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));



	MovementSpeed = 1;
	AttackDamage = DefaultDamage;
}

void AGetGnomedCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	//SetHasRifle(true);

	health = 5;
}

void AGetGnomedCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	invTimer += DeltaSeconds;
	speedUpTimer += DeltaSeconds;
	damageUpTimer += DeltaSeconds;
	isInv = invTimer < invBuffer ? true : false;
	AttackUpEffect = damageUpTimer < damageUpBuffer ? true : false;
	SpeedEffect = speedUpTimer < speedUpBuffer ? true : false;
	if (health <=0)
		isDead = true;
	damageDealt=AttackUpEffect ? defaultDamage*2 : defaultDamage;
	CharacterMovement->MaxWalkSpeed = SpeedEffect ? defaultSpeed * SpeedUp : defaultSpeed;
	
}

//////////////////////////////////////////////////////////////////////////// Input

void AGetGnomedCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGetGnomedCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGetGnomedCharacter::Look);
	}
}

int AGetGnomedCharacter::GetHealth(){
	return health;
}

void AGetGnomedCharacter::SetHealth(int newHealth){
	health = newHealth;
	if (health>maxHealth)
		health=maxHealth;
}

void AGetGnomedCharacter::GetHit(int damage)
{
	if (isInv)
		return;
	health -= damage;
	invTimer=0;
}

void AGetGnomedCharacter::IncreaseSpeed()
{
	//MovementSpeed = NewSpeed;
	speedUpTimer = 0;
	//float WalkSpeed = CharacterMovement->MaxWalkSpeed;
	//CharacterMovement->MaxWalkSpeed = 600.f * NewSpeed;
	//CharacterMovement->MaxFlySpeed = 600.f * NewSpeed;
	//CharacterMovement->GroundFriction = 8.f/NewSpeed;


	//Cast(GetMovementComponent())->MaxWalkSpeed = 100.0f*NewSpeed;
}

void AGetGnomedCharacter::IncreaseDamage()
{
	damageUpTimer=0;
}

float AGetGnomedCharacter::GetSpeedTimer()
{
	return speedUpTimer;
}

float AGetGnomedCharacter::GetDamageTimer()
{
	return damageUpTimer;
}


void AGetGnomedCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AGetGnomedCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGetGnomedCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AGetGnomedCharacter::GetHasRifle()
{
	return bHasRifle;
}