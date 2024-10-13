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

	//������� ��� Volume Actors � ���������� ��� ��������� � GameMode
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

	//������������� ������� ��������� ���� ��� "� �������� ����"
	SetCurrentState(ESnakeGamePlayState::EPlaying);

	APlayerPawnBase* MyCharacter = Cast<APlayerPawnBase>(UGameplayStatics::GetPlayerPawn(this, 0));

	// ���������� HUD �� ������ ������
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
		//����� ��� ������� ����
	case ESnakeGamePlayState::EPlaying:
	{
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			//Volume->SetSpawningActive(true);
		}
	}
	break;
	//����� ����� ��� �������
	case ESnakeGamePlayState::EWon:
	{
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			//Volume->SetSpawningActive(false);
		}
	}
	break;
	//����� ����� ��������
	case ESnakeGamePlayState::EGameOver:
	{
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			//Volume->SetSpawningActive(false);
		}
		GameOver();
	}
	break;
	//����������� ���������, ������������ �� ���������
	default:
	case ESnakeGamePlayState::EUnknown:
	{

	}
	break;
	}

}