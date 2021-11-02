// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cyborg.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDESIGN_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

	//Toggle HUD
	void ToggleInventory();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(AActor* Item);

	void CheckItemAdded(AActor* Item);

	//Will implement later if we add scrapping mechanics
	void RemoveItem();
	
	void AddBoosterPack();

	void AddMaglevPass();

	void AddGunPolish();

	void AddFire();

	ACyborg* Cyborg;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Key: string for the name of the item     Value: int for the number of items 
	TMap<FString, int> Items;

		
};
