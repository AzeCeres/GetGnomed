// Copyright Epic Games, Inc. All Rights Reserved.
// Edited and added onto by Julian
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GetGnomedCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class AGetGnomedCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	
public:
	AGetGnomedCharacter();

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;
public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	int maxHealth{5};
	bool isDead{false};
	UFUNCTION(BlueprintCallable, Category = Health)
	int GetHealth();
	UFUNCTION(BlueprintCallable, Category = Health)
	void SetHealth(int newHealth);
	UFUNCTION(BlueprintCallable, Category = Health)
	void GetHit(int damage);
	int damageDealt{1};
	
private:
	float invTimer{0};
	float invBuffer{.5};
	bool isInv{false};

	// AS junk vv
public:
	//effect stuffs

	UPROPERTY(EditAnywhere, Category = EffectStuffs)
		int health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EffectStuffs)
		bool AttackUpEffect;

	class UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EffectStuffs)
		bool SpeedEffect;

	UFUNCTION(BlueprintCallable, Category = EffectStuffs)
		void IncreaseSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, Category = EffectStuffs)
		void IncreaseDamage(float newDamage);

	//player stats
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerStats)
		float  MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerStats)
		float AttackDamage;

		//player default stats

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerDefaultStats)
		float DefaultDamage = 25;
};

