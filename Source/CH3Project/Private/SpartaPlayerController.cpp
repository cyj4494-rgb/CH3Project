// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaPlayerController.h"
#include "EnhancedInputSubSystems.h"
#include "Blueprint/UserWidget.h"
#include "SpartaGameInstance.h"
#include "SpartaGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
ASpartaPlayerController::ASpartaPlayerController() :
	InputMappingContext(nullptr) , 
	MoveAction(nullptr),
	LookAction(nullptr),
	SprintAction(nullptr),
	JumpAction(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)
{

}

void ASpartaPlayerController::BeginPlay() {

	Super::BeginPlay();

	//로컬 플레이어 정보 가져오기 
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer()) 
	{       //UEnhancedInputLocalPlayerSubsystem을 관리하는 Subsystem 획득하기
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{		// Subsystem에 InputMappingContext 추가하고 우선순위 최우선 (0)
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel")) {
		ShowMainMenu(false);
	}
}

UUserWidget* ASpartaPlayerController::GetHUDWidget() const {
	return HUDWidgetInstance;
}

void ASpartaPlayerController::ShowMainMenu(bool bIsRestart)
{

	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);

		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();

			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());

			UWidget* Widget =
				MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"));

			if (UTextBlock* ButtonText = Cast<UTextBlock>(Widget))
			{
				if (bIsRestart)
				{
					ButtonText->SetText(FText::FromString(TEXT("ReStart")));

				}
				else
				{
					ButtonText->SetText(
						FText::FromString(TEXT("Start")));
				}
			}
			if (bIsRestart) {
				UFunction* PlayAnumFuc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
				if (PlayAnumFuc) {
					MainMenuWidgetInstance->ProcessEvent(PlayAnumFuc, nullptr);
				}

				if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText"))) {
					if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this))) {
						TotalScoreText->SetText(FText::FromString(FString::Printf(TEXT("Total Score : %d"), SpartaGameInstance->TotalScore)));
					}
				}
			}
		}
	}
}

void ASpartaPlayerController::ShowGameHUD() {
	if (HUDWidgetInstance) {
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}
	if (MainMenuWidgetInstance) {
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}
	if (HUDWidgetClass) {
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance) {
			HUDWidgetInstance->AddToViewport();

			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}
		
		ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
		if (SpartaGameState) {
			SpartaGameState->UpdateHUD();
		}
	}

}

void ASpartaPlayerController::StartGame() {
	if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this))) {
		SpartaGameInstance->CurrentLevelIndex = 0;
		SpartaGameInstance->TotalScore = 0;
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));
	SetPause(false);
}