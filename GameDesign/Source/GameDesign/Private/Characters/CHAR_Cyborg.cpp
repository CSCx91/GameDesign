// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CHAR_Cyborg.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"


// Sets default values
ACHAR_Cyborg::ACHAR_Cyborg()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Values for SpringArmComp set in Blueprints
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	StaticMeshComp->SetupAttachment(RootComponent);

	BaseTurnRate = 45.0f;
	BaseLookUpAtRate = 45.0f;

}

// Called when the game starts or when spawned
void ACHAR_Cyborg::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACHAR_Cyborg::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACHAR_Cyborg::MoveVertical(float Value)
{
	if(Controller && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACHAR_Cyborg::MoveHorizontal(float Value)
{
	if(Controller && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ACHAR_Cyborg::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACHAR_Cyborg::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpAtRate * GetWorld()->GetDeltaSeconds());
}

// Called to bind functionality to input
void ACHAR_Cyborg::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveVertical", this, &ACHAR_Cyborg::MoveVertical);
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &ACHAR_Cyborg::MoveHorizontal);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAtRate", this, &ACHAR_Cyborg::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACHAR_Cyborg::LookUpAtRate);

	
	
}

