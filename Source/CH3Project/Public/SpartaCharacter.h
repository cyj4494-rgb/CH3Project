// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class CH3PROJECT_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	float NormalSpeed;
	float SprintSpeed;
	float SprintSpeedMultiplier;
	

public:
	// Sets default values for this character's properties
	ASpartaCharacter();
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly ,Category = "Cameara")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cameara")
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "UI")
	UWidgetComponent* OverHeadWidget;

	UFUNCTION(BlueprintPure , Category = "Health")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);

	

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);

	void OnDeath();
	void UpdateOverHeadHP();

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "health")
	float Health;
};
