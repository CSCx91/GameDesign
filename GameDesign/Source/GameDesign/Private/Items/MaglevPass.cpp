// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/MaglevPass.h"

// Sets default values
AMaglevPass::AMaglevPass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMaglevPass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMaglevPass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

