// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "SnakeBase.h"
#include "Components/InputComponent.h"
#include "Food.h"

// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;

}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90, 0, 0));
	CreateSnakeActor();
	
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BufferTimeForEat += DeltaTime;
	BufferTimeForBonus += DeltaTime;

	if (BufferTimeForEat >= HowOftenSpawnEat)
	{
		RandomSpawnEat();
		BufferTimeForEat = 0;
	}

	if (BufferTimeForBonus >= HowOftenSpawnBonus)
	{
		RandomSpawnBonus();
		BufferTimeForBonus = 0;
	}

}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlerPlayerVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawnBase::HandlerPlayerHorizontalInput);

}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
}

void APlayerPawnBase::HandlerPlayerVerticalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::DOWN)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::UP;
		}
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::UP)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::DOWN;
		}
	}
}

void APlayerPawnBase::HandlerPlayerHorizontalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::RIGHT)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::LEFT;
		}
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::LEFT)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::RIGHT;
		}
	}
}

void APlayerPawnBase::RandomSpawnEat()
{
	float SpawnY = FMath::FRandRange(MinY, MaxY);
	float SpawnX = FMath::FRandRange(MinX, MaxX);
	FRotator StartPointRotation = FRotator(0, 0, 0);

	FVector SpawnPoint = FVector(SpawnX, SpawnY, SpawnZ);
	if (IsValid(SnakeActor))
	{
		if (GetWorld())
		{
			FoodActor = GetWorld()->SpawnActor<AFood>(FoodActorClass, FTransform(SpawnPoint));
		}
	}
}

void APlayerPawnBase::RandomSpawnBonus()
{


	float SpawnY = FMath::FRandRange(MinY, MaxY);
	float SpawnX = FMath::FRandRange(MinX, MaxX);
	FRotator StartPointRotation = FRotator(0, 0, 0);
	int16 WhySpawn = FMath::RandRange(0, 1);
	FVector SpawnPoint = FVector(SpawnX, SpawnY, SpawnZ);

	switch (WhySpawn)
	{
	case 0:
		if (IsValid(SnakeActor))
		{
			if (GetWorld())
			{
				GetWorld()->SpawnActor<AActor>(FirstActorClass, FTransform(SpawnPoint));
			}
		}
		break;
	case 1:
		if (IsValid(SnakeActor))
		{
			if (GetWorld())
			{
				GetWorld()->SpawnActor<AActor>(SecondActorClass, FTransform(SpawnPoint));
			}
		}
		break;

	}
}

