// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Cyborg.generated.h"

UCLASS()
class GAMEDESIGN_API ACyborg : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACyborg();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	int Magazine = 25;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	bool bIsReloadingPrimary = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	bool bIsReloadingSecondary = false;

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

	//Primary fire related functions
	void PrimaryFire();
	void PrimaryFireReleased();
	void FireBullet();
	void ReloadPrimary();
	void ReloadInput();
	void ReloadDone();

	//Secondary fire related functions
	void SecondaryFire();
	void FireRocket();
	void RocketReload();
	
	void Interact();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate;

	//Primary fire timers
	FTimerHandle FireBulletTimer;
	FTimerHandle ReloadTimer;

	//Secondary fire timers
	FTimerHandle FireRocketTimer;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
