// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Inventory.h"


#include "GameFramework/CharacterMovementComponent.h"
#include "Items/DoubleJump.h"
#include "Items/MaglevPass.h"
#include "Items/GunPolish.h"
#include "Items/Fire.h"


// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Cyborg = Cast<ACyborg>(GetOwner());
	
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
	UE_LOG(LogTemp, Warning, TEXT("Adding the item"))
	if(Items.Contains(ItemName))
	{
		Items[ItemName]++;
	}
	else
	{
		Items.Add(ItemName, 1);
	}

	CheckItemAdded(Item);
	
	Item->Destroy();
}

void UInventory::CheckItemAdded(AActor* Item)
{
	if(Item->IsA(ADoubleJump::StaticClass()))
	{
		AddBoosterPack();
	}
	if(Item->IsA(AMaglevPass::StaticClass()))
	{
		AddMaglevPass();
	}

	if (Item->IsA(AGunPolish::StaticClass()))
	{
		AddGunPolish();
	}
	if (Item->IsA(AFire::StaticClass()))
	{
		AddFire();
	}
	
}

void UInventory::AddMaglevPass()
{
	float NewAddedSpeed = (Cyborg->DefaultMovementSpeed * 0.15f);
	Cyborg->MovementSpeedWithItems += NewAddedSpeed;
	Cyborg->CharMovComp->MaxWalkSpeed += NewAddedSpeed;
}

void UInventory::AddFire()
{
	if (Cyborg->FireChance == 0) {
		Cyborg->FireChance = 15.0f;
	}
	else
	{
		Cyborg->FireChance += 2.5f;
	}
}



void UInventory::AddBoosterPack()
{
	Cyborg->JumpMaxCount++;
}

void UInventory::AddGunPolish()
{
	float DecreaseFireRate = Cyborg->BasePrimaryFireRate * 0.08f;
	Cyborg->PrimaryFireRate -= DecreaseFireRate;
}



