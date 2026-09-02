// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MovingMineItem.generated.h"

UCLASS()
class CH3PROJECT_API AMovingMineItem : public ABaseItem
{

	GENERATED_BODY()

public:
	AMovingMineItem();

	USphereComponent* ExplosionCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item");
	float ExplosionDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item");
	float ExplosionDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item");
	int32 ExplosionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects");
	UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects");
	USoundBase* ExplosionSound;
	bool bHasExploded;

	FTimerHandle ExplosionTimerHandle;

	void ActivateItem(AActor* Activator) override;

	void Explode();
};
