// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <tuple>
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Cyborg.generated.h"

class UInventory;


UCLASS()
class GAMEDESIGN_API ACyborg : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACyborg();

	//Primary variables
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	int Magazine = 25;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	bool bIsReloadingPrimary = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	bool bIsReloadingSecondary = false;



	//Utility variables
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	bool bIsUtilityActive = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	bool bIsUtilityReady = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	bool bIsUtilityOnCooldown = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	float UtilCooldown = 12.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	float UtilityActiveTime= 8.0f;


	
	//Health variables

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float DefaultHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	float Health;



	//XP and leveling variables
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float CurrentXP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float CurrentLVL = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float XPRequiredToLVL = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float XPRequiredToLVLPercent = CurrentXP / XPRequiredToLVL;


	
	//Movement variables

	//For items that don't stack with others
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float DefaultMovementSpeed = 600.0f;

	//For items that do stack with others
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float MovementSpeedWithItems = 600.0f;


	//Component variables

	UPROPERTY(VisibleAnywhere)
	UCharacterMovementComponent* CharMovComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventory* InventoryComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	UStaticMeshComponent* MeshComp;


	//Class variable for rockets
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class ARocket> ProjectileClass;

	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Basic movement functions
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Value);
	void LookUpAtRate(float Value);

	//Basic function for all line traces
	std::tuple<bool, AActor*> TraceForward(float Distance);

	//Primary fire related functions
	void PrimaryFire();
	void PrimaryFireReleased();
	void FireBullet();
	void ReloadPrimary();
	void ReloadInput();

	//Secondary fire related functions
	void SecondaryFire();
	void FireRocket();
	void RocketReload();

	//Utility related functions
	void Utility();
	void UtilityDone();
	void UtilityCooldown();

	//Sprint
	void Sprint();
	void StopSprint();

	//Interact functions
	void Interact();

	//XP and Leveling related functions
	void IncreaseLVL();
	void IncreaseXPRequired();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate;


	//Primary variables
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	float PrimaryFireRate = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	float PrimaryFireDamage = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	float PrimaryFireRange = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float RocketReloadTime = 6.0f;
	
	//Interact variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	int InteractDistance = 1000;
	
	//Primary fire timers
	FTimerHandle FireBulletTimer;
	FTimerHandle ReloadTimer;

	//Secondary fire timers
	FTimerHandle FireRocketTimer;
	
	//Utility timers
	FTimerHandle UtilityTimer;
	FTimerHandle UtilityCooldownTimer;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddXP(float xp);

	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
