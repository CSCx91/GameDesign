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

    float BulletExpiry = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool HitObject = false;

    FVector Velocity = FVector(200.0f);
    
    APlayerController* PlayerController;

    UPROPERTY(EditDefaultsOnly, Category = "Spawning")
    TSubclassOf<AActor> ActorToSpawn;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    void DestroySelf();

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void SpawnObject(FVector Loc, FRotator Rot);
};
