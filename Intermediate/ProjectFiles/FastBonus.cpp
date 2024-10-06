// Fill out your copyright notice in the Description page of Project Settings.


#include "FastBonus.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "SnakeBase.h"


// Sets default values
AFastBonus::AFastBonus()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AFastBonus::BeginPlay()
{
	Super::BeginPlay();

	IncreaseSpeed = 0.05f;

}

// Called every frame
void AFastBonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AFastBonus::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			//Reset counter
			Snake->BufferTime = 0;
			Snake->SetActorTickInterval(IncreaseSpeed);
			this->Destroy(true, true);

		}
	}
}