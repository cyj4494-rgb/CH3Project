// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "SpartaGameInstance.h"
#include "CoinItem.h"
#include "SpartaPlayerController.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "BaseItem.h"
#include "SpartaCharacter.h"

ASpartaGameState::ASpartaGameState() {
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	CurrentLevelIndex = 0;
	MaxLevels = 3;

	CurrentWaveIndex = 0;
	MaxWaves = 3;
	WaveSpawnCnt = { 30 , 50 , 80 };
	WaveDuration = { 25.0f , 20.0f , 15.0f};
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&ASpartaGameState::UpdateHUD,
		0.1f,
		true
	);
}
int32 ASpartaGameState::GetScore() const
{
	return Score;
}

void ASpartaGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SPartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SPartaGameInstance) {
			SPartaGameInstance->AddToScore(Amount);
		}
	}
	
}

void ASpartaGameState::StartLevel()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController)) {
			SpartaPlayerController->ShowGameHUD();
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SPartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SPartaGameInstance) {
			CurrentLevelIndex = SPartaGameInstance->CurrentLevelIndex;
		}
	}

	/*SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 40;

	for (int32 i = 0; i < 40; i++) {
		if (FoundVolumes.Num() > 0) {
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume) {
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass())) {
					SpawnedCoinCount++;
				}
			}
		}
	}

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ASpartaGameState::OnLevelTimeUp,
		LevelDuration,
		false
	);*/
	CurrentWaveIndex = 0;

	StartWave();
}

void ASpartaGameState::OnLevelTimeUp() {

	EndWave();
}

void ASpartaGameState::OnCoinCollected() {
	CollectedCoinCount++;

	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount) {
		EndWave();
	}
}

void ASpartaGameState::EndLevel() {
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		USpartaGameInstance* SPartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
		if (SPartaGameInstance) {
			AddScore(Score);
			CurrentLevelIndex++;
			SPartaGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex)) {
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else {
		OnGameOver();
	}
}

void ASpartaGameState::OnGameOver() {
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController)) {
			SpartaPlayerController->SetPause(true);
			SpartaPlayerController->ShowMainMenu(true);
		}
	}
}

void ASpartaGameState::UpdateHUD() {
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController)) {
			if (UUserWidget* HUDWidget = SpartaPlayerController->GetHUDWidget()) {
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time")))) {
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time : %.1f"), RemainingTime)));
				}

				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score")))) {

					if (UGameInstance* GameInstance = GetGameInstance()) {
						USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
						if (SpartaGameInstance) {
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %d"), SpartaGameInstance->TotalScore)));
						}
					}
					
				}
				
				
				if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level")))) {
					
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level : %d"), CurrentLevelIndex + 1)));
				}	

				if (UTextBlock* WaveIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Wave")))) {
					WaveIndexText->SetText(FText::FromString(FString::Printf(TEXT("Wave : %d"), CurrentWaveIndex + 1)));
				}

				ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
				if (UTextBlock* SpeedText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Speed")))) {
					if (SpartaCharacter) {
						SpeedText->SetText(FText::FromString(FString::Printf(TEXT("Speed : %.0f"), SpartaCharacter->GetSpeed())));
					}
					if (SpartaCharacter->IsSlowed())
					{
						SpeedText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
					}
					else
					{
						SpeedText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
					}
				}
			}
		}
	}
}

void ASpartaGameState::StartWave() {
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ASpawnVolume::StaticClass(),FoundVolumes);

	for (int32 i = 0; i < WaveSpawnCnt[CurrentWaveIndex]; i++) {
		if (FoundVolumes.Num() > 0) {
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume) {
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass())) {
					SpawnedCoinCount++;
				}
			}
		}
	}

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ASpartaGameState::OnLevelTimeUp,
		WaveDuration[CurrentWaveIndex],
		false
	);


}

void ASpartaGameState::EndWave() {
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		ABaseItem::StaticClass(),
		Items
	);

	for (AActor* Item : Items)
	{
		if (Item)
		{
			Item->Destroy();
		}
	}

	CurrentWaveIndex++;
	if (CurrentWaveIndex < MaxWaves) {
		StartWave();
	}
	else EndLevel();
}

void ASpartaGameState::EndGame()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		UKismetSystemLibrary::QuitGame(
			GetWorld(),
			PlayerController,
			EQuitPreference::Quit,
			false
		);
	}
}