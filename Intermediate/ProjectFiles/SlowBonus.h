// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"

#include "SlowBonus.generated.h"

UCLASS()
class SNAKEGAME_API ASlowBonus : public ABonusBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASlowBonus();


	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float DecreaseSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Overloading method
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
};