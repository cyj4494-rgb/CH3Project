// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaPlayerController.h"
#include "EnhancedInputSubSystems.h"
#include "Blueprint/UserWidget.h"
#include "SpartaGameState.h"
ASpartaPlayerController::ASpartaPlayerController() :
	InputMappingContext(nullptr) , 
	MoveAction(nullptr),
	LookAction(nullptr),
	SprintAction(nullptr),
	JumpAction(nullptr),
	HUDWidgetClass(nullptr)
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

	if (HUDWidgetClass) {
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
	}
	ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
	if (SpartaGameState) {
		SpartaGameState->UpdateHUD();
	}
}

UUserWidget* ASpartaPlayerController::GetHUDWidget() const {
	return HUDWidgetInstance;
}