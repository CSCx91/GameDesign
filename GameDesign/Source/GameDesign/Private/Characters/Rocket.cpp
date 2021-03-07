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
}

// Called every frame
void ARocket::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FHitResult HitResult;

    FVector StartTrace = this->GetActorLocation();
    FVector EndTrace = (Velocity * DeltaTime) + StartTrace;
    EndTrace.Z += this->GetActorRotation().Pitch;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    BulletExpiry += DeltaTime;
    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Destructible, CollisionParams))
    {
        DrawDebugLine(GetWorld(), HitResult.ImpactPoint, FVector(10.f), FColor::Red, true);
        if (HitResult.GetActor())
        {
            DrawDebugSolidBox(GetWorld(), HitResult.ImpactPoint, FVector(10.f), FColor::Blue, true);
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Fire")));
        }

        Destroy();
    }
    else
    {

        DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Orange, true);

        SetActorLocation(EndTrace);

        Velocity += FVector(0.f, 0.f, -200.f) * DeltaTime;
    }

    if (BulletExpiry > 3)
    {
        Destroy();
    }
}
