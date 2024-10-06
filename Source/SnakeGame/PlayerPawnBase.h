// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawnBase.generated.h"

class UCameraComponent;
class ASnakeBase;
class AFood;
class APortal;

UCLASS()
class SNAKEGAME_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* PawnCamera;

	UPROPERTY(BlueprintReadWrite)
	ASnakeBase* SnakeActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeBase> SnakeActorClass;

	//A range for Creating Food/Bonus by Y
	UPROPERTY(EditAnyWhere)
	float MinY = -1350.f; float MaxY = 1340.f;
	//A range for Creating Food/Bonus by X
	UPROPERTY(EditAnyWhere)
	float MinX = -1330.f; float MaxX = 1320.f;
	// Creating Foot by Z
	UPROPERTY()
	float SpawnZ = 2.f;

	UPROPERTY()
	float BufferTimeForEat = 0;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float HowOftenSpawnEat = 1.f;

	UPROPERTY(BlueprintReadWrite)
	AFood* FoodActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodActorClass;

	//For fu RandomSpawnBonus
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Bonus's spawn")
	TSubclassOf<AActor> FirstActorClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Bonus's spawn")
	TSubclassOf<AActor> SecondActorClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Bonus's spawn")
	float HowOftenSpawnBonus = 2.f;
	UPROPERTY()
	float BufferTimeForBonus;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CreateSnakeActor();

	UFUNCTION()
	void HandlerPlayerVerticalInput(float value);

	UFUNCTION()
	void HandlerPlayerHorizontalInput(float value);

	UFUNCTION()
	void RandomSpawnEat();
	UFUNCTION(BlueprintCallable)
	void RandomSpawnBonus();

};
