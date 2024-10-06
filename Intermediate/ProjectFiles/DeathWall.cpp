// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathWall.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "SnakeBase.h"

// Sets default values
ADeathWall::ADeathWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void ADeathWall::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADeathWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathWall::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(Snake))
	{
		Snake->Destroy(true, true);
	}
}