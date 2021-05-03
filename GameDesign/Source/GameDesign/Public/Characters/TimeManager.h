// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

UCLASS()
class GAMEDESIGN_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeManager();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
	float DifficultyValue = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
	float DifficultyThreshold = 60.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle DifficultyIncreaseTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void UpdateDifficultyValue();
	

};
