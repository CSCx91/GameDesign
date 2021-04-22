// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Inventory.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UInventory::ToggleInventory()
{
	
}

void UInventory::AddItem(AActor* Item)
{
	const FString ItemName = Item->GetName();
	if(Items.Contains(ItemName))
	{
		Items[ItemName]++;
	}
	else
	{
		Items.Add(ItemName, 1);
	}
}

