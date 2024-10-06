// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABonusBase::ABonusBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshActor's"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

}

// Called when the game starts or when spawned
void ABonusBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABonusBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FloatingActor(DeltaTime);

	BufferTime += DeltaTime;

	if (BufferTime >= TimeLiving)
	{
		this->Destroy(true, true);
		BufferTime = 0;
	}
}

void ABonusBase::FloatingActor(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

	NewLocation.Z += DeltaHeight * FloatSpeed;
	float DeltaRotation = DeltaTime * RotationSpeed;
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);

}