// Copyright Epic Games, Inc. All Rights Reserved.
// Edited and added onto by Julian&co
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "UnrealWidgetFwd.h"
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


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PauseAction;

	
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
	UPROPERTY(BlueprintReadOnly)
	int maxHealth{5};
	bool isDead{false};
	UFUNCTION(BlueprintCallable, Category = Health)
	int GetHealth();
	UFUNCTION(BlueprintCallable, Category = Health)
	void SetHealth(int newHealth);
	UFUNCTION(BlueprintCallable, Category = Health)
	void GetHit(int damage);
	UPROPERTY(BlueprintReadOnly)
	int damageDealt{1};

	
	UPROPERTY(EditInstanceOnly,BlueprintReadOnly, Category = EffectStuffs)
	float damageUpBuffer{10};
	UPROPERTY(EditInstanceOnly,BlueprintReadOnly, Category = EffectStuffs)
	float speedUpBuffer{10};
	UPROPERTY(BlueprintReadOnly, Category = EffectStuffs)
	float damageUpTimer{damageUpBuffer};
	UPROPERTY(BlueprintReadOnly, Category = EffectStuffs)
	float speedUpTimer{speedUpBuffer};
	UPROPERTY(EditInstanceOnly,BlueprintReadOnly, Category = EffectStuffs)
	float SpeedUp{1.5};
private:
	float invTimer{0};
	float invBuffer{.5};
	bool isInv{false};
	int defaultDamage{1};
	float defaultSpeed{600};

	bool ExtraPaused{ false };

	
	
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
		void IncreaseSpeed();

	UFUNCTION(BlueprintCallable, Category = EffectStuffs)
		void IncreaseDamage();
	UFUNCTION(BlueprintCallable, Category = EffectStuffs)
			float GetSpeedTimer();
	UFUNCTION(BlueprintCallable, Category = EffectStuffs)
			float GetDamageTimer();
	//player stats
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerStats)
		float  MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerStats)
		float AttackDamage;

		//player default stats

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerDefaultStats)
		float DefaultDamage = 25;

	UFUNCTION(BlueprintCallable, Category = EffectStuffs)
		void PauseGame();

	UFUNCTION(BlueprintCallable, Category = EffectStuffs)
		void EndGame(int CurrentScore);

	UFUNCTION(BlueprintCallable, Category = EffectStuffs)
		void UnExtraPause();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Widget")
		void ShowWin();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Widget")
		void ShowLoss();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HighScore")
		int TotScore {0};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HighScore")
		int HighScoreCurrent;

	UFUNCTION(BlueprintCallable, Category = "HighScore")
		void UpdateGameScore(int newScore);


};

