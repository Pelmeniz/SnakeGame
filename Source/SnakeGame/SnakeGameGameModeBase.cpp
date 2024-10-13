// Copyright Epic Games, Inc. All Rights Reserved.


#include "SnakeGameGameModeBase.h"

#include "PlayerPawnBase.h"
#include "SpawnVolume.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void ASnakeGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Находим все Volume Actors и записываем для обработки в GameMode
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

	//Устанавливаем текущее состояние игры как "в процессе игры"
	SetCurrentState(ESnakeGamePlayState::EPlaying);

	APlayerPawnBase* MyCharacter = Cast<APlayerPawnBase>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Показываем HUD на экране игрока
	if (HUDWidgetClass != nullptr)
	{
		CurrentHUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentHUDWidget != nullptr)
		{
			CurrentHUDWidget->AddToViewport();
		}
	}
}

ESnakeGamePlayState ASnakeGameGameModeBase::GetCurrentState() const
{
	return CurrentState;
}

void ASnakeGameGameModeBase::SetCurrentState(ESnakeGamePlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

void ASnakeGameGameModeBase::GameOver()
{
	CurrentGameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
	if (CurrentGameOverWidget != nullptr)
	{
		CurrentGameOverWidget->AddToViewport();
		APlayerController* CurrentPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(CurrentPlayerController, CurrentGameOverWidget,
			EMouseLockMode::LockAlways);
		CurrentPlayerController->bShowMouseCursor = true;
		SetPause(CurrentPlayerController);
	}
	//GameOverDelegate.Broadcast();
}

void ASnakeGameGameModeBase::HandleNewState(ESnakeGamePlayState NewState)
{
	switch (NewState)
	{
		//Когда идёт процесс игры
	case ESnakeGamePlayState::EPlaying:
	{
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			//Volume->SetSpawningActive(true);
		}
	}
	break;
	//Когда игрок уже победил
	case ESnakeGamePlayState::EWon:
	{
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			//Volume->SetSpawningActive(false);
		}
	}
	break;
	//Когда игрок проиграл
	case ESnakeGamePlayState::EGameOver:
	{
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			//Volume->SetSpawningActive(false);
		}
		GameOver();
	}
	break;
	//Неизвестное состояние, используется по умолчанию
	default:
	case ESnakeGamePlayState::EUnknown:
	{

	}
	break;
	}

}