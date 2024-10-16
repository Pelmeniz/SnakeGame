// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"
#include "SnakeGameGameModeBase.h"
#include "Engine/SceneCapture2D.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 150.f;
	MovementSpeed = 1.f;
	LastMovementDirection = EMovementDirection::DOWN;

}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed); 
	AddSnakeElement(5);
	
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}


void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewLocation;
		if (SnakeElements.Num() > 0)
		{
			ASnakeElementBase* LastElement = SnakeElements.Last();
			FVector LastLocation = LastElement->GetActorLocation();
			switch (LastMovementDirection)
			{
			case EMovementDirection::UP:
				NewLocation = LastLocation - FVector(ElementSize, 0, 0);
				break;
			case EMovementDirection::DOWN:
				NewLocation = LastLocation + FVector(ElementSize, 0, 0);
				break;
			case EMovementDirection::LEFT:
				NewLocation = LastLocation - FVector(0, ElementSize, 0);
				break;
			case EMovementDirection::RIGHT:
				NewLocation = LastLocation + FVector(0, ElementSize, 0);
				break;
			}
		
		}
		else
		{
			NewLocation = FVector(0, 0, 0);
		}
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElem->SnakeOwner = this;
		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		
		if (ElemIndex == 0)
		{
			NewSnakeElem->SetFirstElementType();
		}
	}

}

void ASnakeBase::Move() 
{
	FVector MovementVector(ForceInitToZero);
	if (Mooving == false)
	{
		switch (LastMovementDirection)
		{
		case EMovementDirection::UP:
			MovementVector.X += ElementSize;
			Mooving = false;
			break;
		case EMovementDirection::DOWN:
			MovementVector.X -= ElementSize;
			Mooving = false;
			break;
		case EMovementDirection::LEFT:
			MovementVector.Y += ElementSize;
			Mooving = false;
			break;
		case EMovementDirection::RIGHT:
			MovementVector.Y -= ElementSize;
			Mooving = false;
			break;
		}
	}

	//AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
	SnakeElements[0]->SetHidden(false);

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
		CurrentElement->SetHidden(false);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
	
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
		}
		else
		{
			ASnakeGameGameModeBase* CurrentGameModeBase = Cast<ASnakeGameGameModeBase>(
				UGameplayStatics::GetGameMode(GetWorld()));
			CurrentGameModeBase->SetCurrentState(ESnakeGamePlayState::EGameOver);
		}
	}
}
int32 ASnakeBase::GetElementsCount() const
{
	return SnakeElements.Num();
}


