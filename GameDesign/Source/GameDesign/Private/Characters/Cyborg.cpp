// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Cyborg.h"

#include <string>

#include "DrawDebugHelpers.h"
#include "Characters/Inventory.h"
#include "Characters/Rocket.h"
#include "Characters/SpiderBomber.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACyborg::ACyborg()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	MeshComp->SetupAttachment(RootComponent);

	BarrelEndpoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"));
	BarrelEndpoint->SetupAttachment(GetMesh(), "ForeArm_L_end");
	

	CharMovComp = GetCharacterMovement();

	InventoryComp = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	Health = DefaultHealth;
	
	UtilityDel.BindUFunction(this, FName("UtilityDone"), PrimaryFireAtActivate, RocketReloadAtActivate, MovementSpeedWithItems);
	
}

// Called when the game starts or when spawned
void ACyborg::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ACyborg::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACyborg::MoveForward(float Value)
{
	if(Controller && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACyborg::MoveRight(float Value)
{
	if(Controller && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ACyborg::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACyborg::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

std::tuple<bool, AActor*> ACyborg::TraceForward(float Distance)
{
	FVector Location;
	FRotator Rotation;
	FHitResult Hit;

	GetController()->GetPlayerViewPoint(Location, Rotation);

	FVector Start = BarrelEndpoint->GetComponentLocation();
	FVector End = Start + (Rotation.Vector() * Distance);

	FCollisionQueryParams TraceParams;
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);
	
	if(bHit)
		return {bHit, Hit.GetActor()};

	return {bHit, nullptr};
}



void ACyborg::PrimaryFire()
{
	FireBullet();
	GetWorldTimerManager().SetTimer(FireBulletTimer, this, &ACyborg::FireBullet, PrimaryFireRate, true);
}

void ACyborg::PrimaryFireReleased()
{
	GetWorldTimerManager().ClearTimer(FireBulletTimer);
}

void ACyborg::FireBullet()
{
	//As long as the player continues to hold fire and has bullets, fire them
	if(Magazine >= 1 && !bIsReloadingPrimary)
	{
		Magazine--;

		std::tuple<bool, AActor*> BulletTrace = TraceForward(PrimaryFireRange);
		bool bHit = std::get<0>(BulletTrace);
		AActor* HitActor = std::get<1>(BulletTrace);
		
		if(bHit && HitActor)
		{
		    HitActor->TakeDamage(PrimaryFireDamage, FDamageEvent(), GetController(), this);
		}
	}
	//If the player isn't currently reloading and has hit 0 bullets left
	if(Magazine == 0 && !bIsReloadingPrimary)
	{
		bIsReloadingPrimary = true;
		GetWorldTimerManager().SetTimer(ReloadTimer, this, &ACyborg::ReloadPrimary, 2.5f, false);
	}
}

//This function is called once reloading is done aka when the timer is completed
void ACyborg::ReloadPrimary()
{
	//UE_LOG(LogTemp, Warning, TEXT("Reloading"));
	Magazine = 25;
	bIsReloadingPrimary = false;
}

void ACyborg::ReloadInput()
{
	//If no reload timer is active, start one
	if(!GetWorldTimerManager().IsTimerActive(ReloadTimer))
	{
		if(GetWorldTimerManager().IsTimerActive(FireBulletTimer))
			GetWorldTimerManager().ClearTimer(FireBulletTimer);
		
		bIsReloadingPrimary = true;
		GetWorldTimerManager().SetTimer(ReloadTimer, this, &ACyborg::ReloadPrimary, 2.5f, false);
	}
}


void ACyborg::SecondaryFire()
{
	if(!bIsReloadingSecondary)
	{
		bIsReloadingSecondary = true;
		FireRocket();
		GetWorldTimerManager().SetTimer(FireRocketTimer, this, &ACyborg::RocketReload, RocketReloadTime, false);
	}
	
}

void ACyborg::FireRocket()
{
	FVector Location;
	FRotator Rotation;

	GetController()->GetPlayerViewPoint(Location, Rotation);

	if (ProjectileClass != NULL)
	{
		FRotator SpawnRotation = Rotation;
		FVector SpawnLocation = BarrelEndpoint->GetComponentLocation();
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			ARocket* Rocket = World->SpawnActor<ARocket>(ProjectileClass, SpawnLocation, SpawnRotation);
			FVector NewVelocity = SpawnRotation.Vector() * 8000.0f;
			Rocket->Velocity = FVector(NewVelocity);
		}
	}
}

void ACyborg::RocketReload()
{
	bIsReloadingSecondary = false;
}



void ACyborg::Utility()
{
	if (bIsUtilityReady)
	{
		bIsUtilityActive = true;
		bIsUtilityReady = false;
		PrimaryFireAtActivate = PrimaryFireRate;
		PrimaryFireRate -= (PrimaryFireAtActivate / 2);
		RocketReloadTime -= (RocketReloadAtActivate / 2);
		CharMovComp->MaxWalkSpeed += (MovementSpeedWithItems * 0.20);
	}

	GetWorldTimerManager().SetTimer(UtilityTimer, UtilityDel, UtilityActiveTime, false);
}

void ACyborg::UtilityDone(float PrimaryFireRateAtActive, float RocketReloadTimeAtActive, float MovementSpeedAtActive)
{
	if(!bIsUtilityOnCooldown)
	{
		PrimaryFireRate += (PrimaryFireRateAtActive / 2);
		RocketReloadTime += (RocketReloadTimeAtActive / 2);
		CharMovComp->MaxWalkSpeed -= (MovementSpeedAtActive * 0.20f);
		bIsUtilityOnCooldown = true;
		bIsUtilityActive = false;
		GetWorldTimerManager().SetTimer(UtilityCooldownTimer, this, &ACyborg::UtilityCooldown, UtilCooldown, false);
	}
}

void ACyborg::UtilityCooldown()
{
	bIsUtilityReady = true;
	bIsUtilityOnCooldown = false;
}

void ACyborg::Sprint()
{
	LastMovementSpeedBeforeSprint = CharMovComp->MaxWalkSpeed;	
	CharMovComp->MaxWalkSpeed += (LastMovementSpeedBeforeSprint * 0.50f);
	
}

void ACyborg::StopSprint()
{
	CharMovComp->MaxWalkSpeed -= (LastMovementSpeedBeforeSprint * 0.50f);
}


void ACyborg::AddXP(float xp)
{
	CurrentXP += xp;
	if (CurrentXP >= XPRequiredToLVL)
	{
		IncreaseLVL();
	}

}

void ACyborg::IncreaseLVL()
{
	CurrentXP = CurrentXP - XPRequiredToLVL;
	CurrentLVL += 1.0;
	IncreaseXPRequired();
}

void ACyborg::IncreaseXPRequired()
{
	XPRequiredToLVL *= 2;
}



void ACyborg::Interact()
{
	std::tuple<bool, AActor*> InteractTrace = TraceForward(InteractDistance);
	bool bHit = std::get<0>(InteractTrace);
	AActor* HitActor = std::get<1>(InteractTrace);
	
	if(bHit && HitActor)
	{
		if(HitActor->ActorHasTag("Item"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Found item!"))
			InventoryComp->AddItem(HitActor);
		}
	}
}


// Called to bind functionality to input
void ACyborg::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("PrimaryFire", IE_Pressed, this, &ACyborg::PrimaryFire);
	PlayerInputComponent->BindAction("PrimaryFire", IE_Released, this, &ACyborg::PrimaryFireReleased);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ACyborg::ReloadInput);
	PlayerInputComponent->BindAction("SecondaryFire", IE_Pressed, this, &ACyborg::SecondaryFire);
	PlayerInputComponent->BindAction("Utility", IE_Pressed, this, &ACyborg::Utility);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACyborg::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACyborg::StopSprint);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACyborg::Interact);
	
	PlayerInputComponent->BindAxis("MoveForward",this, &ACyborg::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this, &ACyborg::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn",this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACyborg::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACyborg::LookUpAtRate);

}

