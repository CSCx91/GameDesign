// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Cyborg.h"
#include "DrawDebugHelpers.h"
#include "Characters/Rocket.h"

// Sets default values
ACyborg::ACyborg()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	MeshComp->SetupAttachment(RootComponent);

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;
	
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

//Will change to fire while held down
void ACyborg::PrimaryFire()
{
	FireBullet();
	GetWorldTimerManager().SetTimer(FireBulletTimer, this, &ACyborg::FireBullet, 0.2f, true);
}

void ACyborg::PrimaryFireReleased()
{
	GetWorldTimerManager().ClearTimer(FireBulletTimer);
}

void ACyborg::FireBullet()
{
	if(Magazine >= 1)
	{
		Magazine--;
		FVector Location;
		FRotator Rotation;
		FHitResult Hit;

		GetController()->GetPlayerViewPoint(Location, Rotation);

		FVector Start = Location;
		FVector End = Start + (Rotation.Vector() * 2000);

		FCollisionQueryParams TraceParams;
		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);
	}
	if(Magazine == 0)
	{
		GetWorldTimerManager().SetTimer(ReloadTimer, this, &ACyborg::ReloadPrimary, 2.5f, false);
	}
}

void ACyborg::ReloadPrimary()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading"));
	Magazine = 25;
}


void ACyborg::SecondaryFire()
{
	FireRocket();
}

void ACyborg::FireRocket()
{
	FVector Location;
	FRotator Rotation;
	FHitResult Hit;

	GetController()->GetPlayerViewPoint(Location, Rotation);

	FVector Start = Location;
	FVector End = Start + (Rotation.Vector() * 2000);

	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		const FVector SpawnLocation = Location + (Rotation.Vector() * 2000);
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			ARocket* Rocket = World->SpawnActor<ARocket>(ProjectileClass, Start, SpawnRotation);
			FVector NewVelocity = GetActorForwardVector() * 3000.f;

			Rocket->Velocity = FVector(NewVelocity);
		}
	}
}

void ACyborg::Interact()
{
	FVector Location;
	FRotator Rotation;
	FHitResult Hit;

	GetController()->GetPlayerViewPoint(Location, Rotation);

	FVector Start = Location;
	FVector End = Start + (Rotation.Vector() * 700);
    
	FCollisionQueryParams TraceParams;
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 2.0f);
}

// Called to bind functionality to input
void ACyborg::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("PrimaryFire", IE_Pressed, this, &ACyborg::PrimaryFire);
	PlayerInputComponent->BindAction("PrimaryFire", IE_Released, this, &ACyborg::PrimaryFireReleased);
	PlayerInputComponent->BindAction("SecondaryFire", IE_Pressed, this, &ACyborg::SecondaryFire);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACyborg::Interact);
	
	PlayerInputComponent->BindAxis("MoveForward",this, &ACyborg::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this, &ACyborg::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn",this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACyborg::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACyborg::LookUpAtRate);

}

