// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"

#include "BaseItem.generated.h"

class USphereComponent;

UCLASS()
class CH3PROJECT_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseItem();

protected:

	virtual void OnItemOverlap(
		UPrimitiveComponent* overlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	virtual void OnItemEndOverlap(
		UPrimitiveComponent* overlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

	virtual void ActivateItem(AActor* Activator) override;
	virtual FName GetItemType() const override;

	void DestroyItem();

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Item");
	FName ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component");
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component");
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component");
	USphereComponent* Collision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects");
	UParticleSystem* PickupParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects");
	USoundBase* PickupSound;
};
