// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rocket.generated.h"

UCLASS()
class GAMEDESIGN_API ARocket : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ARocket();

    USceneComponent* RootComp;

    UPROPERTY(EditAnywhere)
        FVector Velocity = FVector(100.f);

    float BulletExpiry = 0;
    
    APlayerController* PlayerController; 

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
