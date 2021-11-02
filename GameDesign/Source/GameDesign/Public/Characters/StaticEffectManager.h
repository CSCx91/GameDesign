// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaticEffectManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDESIGN_API UStaticEffectManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaticEffectManager();

	//fire
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	float FireDamage = 4.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	float IncreaseFireDamage = 1.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
