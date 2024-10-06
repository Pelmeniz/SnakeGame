#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "BonusBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class SNAKEGAME_API ABonusBase : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABonusBase();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "BodyActor's")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "FloatingActor")
	float FloatSpeed = 20.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "FloatingActor")
	float RotationSpeed = 20.0f;

	UPROPERTY()
	float BufferTime = 0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float TimeLiving = 5.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void FloatingActor(float DeltaTime);
};