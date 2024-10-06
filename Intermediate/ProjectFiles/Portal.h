// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Portal.generated.h"

class UStaticMeshComponent;

UCLASS()
class SNAKEGAME_API APortal : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APortal();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "BodyActor's")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY()
	TArray<AActor*>Portals;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//Overloading method
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
};