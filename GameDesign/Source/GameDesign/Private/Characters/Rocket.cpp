// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Rocket.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

// Sets default values
ARocket::ARocket()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
    RootComponent = RootComp;
}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
    Super::BeginPlay();
    
    PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
}

// Called every frame
void ARocket::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FHitResult HitResult;

    FVector PlayerLocation;
    FRotator PlayerRotation;

    FVector StartTrace = this->GetActorLocation();
    FVector EndTrace = (Velocity * DeltaTime) + StartTrace;
    PlayerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

    FVector Start = this->GetActorLocation();
    FVector End = Start + (PlayerRotation.Vector() * 2000);
    
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    BulletExpiry += DeltaTime;
    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, CollisionParams))
    {
        DrawDebugLine(GetWorld(), HitResult.ImpactPoint, FVector(10.f), FColor::Red, true);
        UWorld* const World = GetWorld();
        if (HitResult.GetActor())
        {
            DrawDebugSolidBox(GetWorld(), HitResult.ImpactPoint, FVector(10.f), FColor::Blue, true);
            UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.GetActor()->GetName());
            bHitObject = true;
            
        }
        else
        {
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Rocket hit nothing")));
        }
    }
    else
    {

        DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Orange, true);

        SetActorLocation(EndTrace);
        
        //First testing it out without gravity
        Velocity += FVector(0.f, 0.f, -400.f) * DeltaTime;
    }

    if (BulletExpiry > 5)
    {
        Destroy();
    }
}

