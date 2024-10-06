// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowBonus.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "SnakeBase.h"

// Sets default values
ASlowBonus::ASlowBonus()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ASlowBonus::BeginPlay()
{
	Super::BeginPlay();

	DecreaseSpeed = 0.9f;
}

// Called every frame
void ASlowBonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlowBonus::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			//Reset counter
			Snake->BufferTime = 0;
			Snake->SetActorTickInterval(DecreaseSpeed);
			this->Destroy(true, true);

		}
	}
}