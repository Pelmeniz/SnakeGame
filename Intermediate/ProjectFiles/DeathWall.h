#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "DeathWall.generated.h"

class UStaticMeshComponent;

UCLASS()
class SNAKEGAME_API ADeathWall : public AActor, public IInteractable
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ADeathWall();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Overloaiding method
	virtual void Interact(AActor* Interactor, bool bIsHead) override;


};