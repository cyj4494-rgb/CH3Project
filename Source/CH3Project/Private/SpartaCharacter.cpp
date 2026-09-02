// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaCharacter.h"
#include "EnhancedInputComponent.h"
#include "SpartaPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/TextBlock.h"
#include "SpartaGameState.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASpartaCharacter::ASpartaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp , USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	OverHeadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadWidget"));
	OverHeadWidget->SetupAttachment(GetMesh());
	OverHeadWidget->SetWidgetSpace(EWidgetSpace::Screen);

	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.7f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;
	

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	MaxHealth = 100.0f;
	Health = MaxHealth;

	bIsSlowed = false;
	bIsSprinting = false;
	SlowMultiplier = 0.5f;
}


// Called to bind functionality to input
void ASpartaCharacter::BeginPlay() {
	Super::BeginPlay();
	UpdateOverHeadHP();
}
void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Move
				);
			}
			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::StartJump
				);
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopJump
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Look
				);
			}
			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::StartSprint
				);
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopSprint
				);
			}
		}
	}
}

void ASpartaCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X)) {
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y)) {
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void ASpartaCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>()) {
		Jump();
	}
}

void ASpartaCharacter::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>()) {
		StopJumping();
	}
}

void ASpartaCharacter::Look(const FInputActionValue& value)
{
	const FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ASpartaCharacter::StartSprint(const FInputActionValue& value)
{
	bIsSprinting = true;

	if (GetCharacterMovement()) {
		if (bIsSlowed) {
			GetCharacterMovement()->MaxWalkSpeed = SprintSpeed * SlowMultiplier;
		}
		else {
			GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		}
	}
}

void ASpartaCharacter::StopSprint(const FInputActionValue& value)
{
	bIsSprinting = false;

	if (GetCharacterMovement()) {
		if (bIsSlowed) {
			GetCharacterMovement()->MaxWalkSpeed = NormalSpeed * SlowMultiplier;
		}
		else {
			GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
		}
	}
}

void ASpartaCharacter::OnDeath() {
	ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
	if (SpartaGameState) {
		SpartaGameState->OnGameOver();
	}
}

float ASpartaCharacter::GetHealth() const {
	return Health;
}

void ASpartaCharacter::AddHealth(float Amount)
{
	
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
	UpdateOverHeadHP();
}

float ASpartaCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
	UpdateOverHeadHP();
	if (Health <= 0.0f) {
		OnDeath();
	}
	return ActualDamage;
}

void ASpartaCharacter::UpdateOverHeadHP() {
	if (!OverHeadWidget) return;

	UUserWidget* OverHeadWidgetInstance = OverHeadWidget->GetUserWidgetObject();

	if (!OverHeadWidgetInstance) return;

	if (UTextBlock* HPText = Cast<UTextBlock>(OverHeadWidgetInstance->GetWidgetFromName(TEXT("OverHeadHP")))) {
		HPText->SetText(FText::FromString(FString::Printf(TEXT("%0.f / %0.f"), Health, MaxHealth)));
	}
}

void ASpartaCharacter::ApplySlow()
{
	bIsSlowed = true;

	if (GetCharacterMovement())
	{
		if (bIsSprinting)
		{
			GetCharacterMovement()->MaxWalkSpeed =
				SprintSpeed * SlowMultiplier;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed =
				NormalSpeed * SlowMultiplier;
		}
	}

	GetWorldTimerManager().SetTimer(
		SlowTimerHandle,
		this,
		&ASpartaCharacter::RemoveSlow,
		3.0f,
		false
	);
}

void ASpartaCharacter::RemoveSlow() {
	bIsSlowed = false;

	if (GetCharacterMovement())
	{
		if (bIsSprinting)
		{
			GetCharacterMovement()->MaxWalkSpeed =
				SprintSpeed;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed =
				NormalSpeed;
		}
	}
}

float ASpartaCharacter::GetSpeed() const {
	return GetCharacterMovement()->MaxWalkSpeed;
}

bool ASpartaCharacter::IsSlowed() {
	return bIsSlowed;
}