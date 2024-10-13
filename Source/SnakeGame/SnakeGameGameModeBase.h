// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SnakeGameGameModeBase.generated.h"

class ASpawnVolume;

//Enum ��� ����������� ������� ���������
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

	/**���������� ������� ��������� ����*/
	UFUNCTION(BlueprintPure)
	ESnakeGamePlayState GetCurrentState() const;

	void SetCurrentState(ESnakeGamePlayState NewState);

	UFUNCTION(BlueprintCallable)
	void GameOver();

	UPROPERTY(BlueprintAssignable)
	FGameOverSignature GameOverDelegate;
protected:
	/**����� �������, ������� ����������� �� ����� ��� HUD*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
	TSubclassOf<UUserWidget> HUDWidgetClass;

	/**������� ������� HUD, � ������� �������� GameMode. �� ��������� ������������ �� ��������� ����� ������.*/
	UPROPERTY()
	class UUserWidget* CurrentHUDWidget;

	/**����� �������, ������� ����������� �� ����� ��� HUD*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	/**������� ������� ������ GameOver, � ������� �������� GameMode. �� ��������� ������������ �� ��������� ����� ������.*/
	UPROPERTY()
	class UUserWidget* CurrentGameOverWidget;

private:
	/**������� ��������� ����*/
	ESnakeGamePlayState CurrentState;

	TArray<class ASpawnVolume*> SpawnVolumeActors;

	/**Handle any function calls that rely upon changing the playing state of our game */
	void HandleNewState(ESnakeGamePlayState NewState);
};
