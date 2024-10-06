// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/StaticMeshComponent.h"
#include "SnakeBase.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeElementBase.h"




// Sets default values
APortal::APortal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshActor's"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APortal::StaticClass(), Portals);

}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


void APortal::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = (Cast<ASnakeBase>(Interactor));
		if (IsValid(Snake))
		{
			int16 NumPortal = FMath::RandRange(0, (Portals.Num() - 1));
			FVector NewLocation = Portals[NumPortal]->GetActorLocation();
			Snake->SnakeElements[0]->SetActorLocation(NewLocation);
		}
	}
}