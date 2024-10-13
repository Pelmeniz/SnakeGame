// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SnakeGameGameModeBase.generated.h"

class ASpawnVolume;

//Enum для обозначения игровых состояний
UENUM(BlueprintType)
enum class ESnakeGamePlayState : uint8
{
	EPlaying
	UMETA(DisplayName = "Playing"),
	EGameOver
	UMETA(DisplayName = "Game Over"),
	EWon
	UMETA(DisplayName = "Won"),
	EUnknown
	UMETA(DisplayName = "Unknown"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverSignature);

UCLASS(MinimalAPI)
class ASnakeGameGameModeBase : public AGameMode 
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	/**Возвращает текущее состояние игры*/
	UFUNCTION(BlueprintPure)
	ESnakeGamePlayState GetCurrentState() const;

	void SetCurrentState(ESnakeGamePlayState NewState);

	UFUNCTION(BlueprintCallable)
	void GameOver();

	UPROPERTY(BlueprintAssignable)
	FGameOverSignature GameOverDelegate;
protected:
	/**Класс виджета, который добавляется на экран как HUD*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
	TSubclassOf<UUserWidget> HUDWidgetClass;

	/**Инстанс виджета HUD, с которым работает GameMode. Не требуется использовать за пределами этого класса.*/
	UPROPERTY()
	class UUserWidget* CurrentHUDWidget;

	/**Класс виджета, который добавляется на экран как HUD*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	/**Инстанс виджета экрана GameOver, с которым работает GameMode. Не требуется использовать за пределами этого класса.*/
	UPROPERTY()
	class UUserWidget* CurrentGameOverWidget;

private:
	/**Текущее состояние игры*/
	ESnakeGamePlayState CurrentState;

	TArray<class ASpawnVolume*> SpawnVolumeActors;

	/**Handle any function calls that rely upon changing the playing state of our game */
	void HandleNewState(ESnakeGamePlayState NewState);
};
