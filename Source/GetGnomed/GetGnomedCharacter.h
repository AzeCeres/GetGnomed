// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
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


public:
	//effect stuffs
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EffectStuffs)
		bool SpeedEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EffectStuffs)
		bool AttackUpEffect;


	UFUNCTION(BlueprintCallable, Category = EffectStuffs)
		void IncreaseHealth();

	UFUNCTION(BlueprintCallable, Category = EffectStuffs)
		void IncreaseSpeed();

	UFUNCTION(BlueprintCallable, Category = EffectStuffs)
		void IncreaseDamage();

	//player stats
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerStats)
		float MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerStats)
		float AttackDamage;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerStats)
		float PlayerHealth;*/

	//player default stats

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerDefaultStats)
		float DefaultDamage = 25;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerDefStats)
		float MaxHealth = 100;*/
};

