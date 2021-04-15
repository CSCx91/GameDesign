// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/DoubleJump.h"

// Sets default values
ADoubleJump::ADoubleJump()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoubleJump::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoubleJump::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

