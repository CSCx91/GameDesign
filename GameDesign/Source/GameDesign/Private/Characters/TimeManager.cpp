// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TimeManager.h"
#include "TimerManager.h"


// Sets default values
ATimeManager::ATimeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATimeManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DifficultyIncreaseTimer, this, &ATimeManager::UpdateDifficultyValue, DifficultyThreshold, true);
}

// Called every frame
void ATimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATimeManager::UpdateDifficultyValue()
{
	if(DifficultyValue < 5.0f)
	{
		DifficultyValue += 0.20f;
		UE_LOG(LogTemp, Warning, TEXT("Updating difficulty"))
		return;
	}
		
	if(DifficultyValue >= 5.0f)
	{
		DifficultyValue += 0.25f;
		return;
	}
	
	if(DifficultyValue <= 10.0f)
	{
		DifficultyValue += 0.5f;
		return;
	}
	
}


