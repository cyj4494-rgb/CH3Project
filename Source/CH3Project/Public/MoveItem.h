// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveItem.generated.h"

UCLASS()
class CH3PROJECT_API AMoveItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Components")
	USceneComponent* RootScene;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float MaxRange;
	float MoveCount;
	float Flow_Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int X_Y_Z;

	FVector StartLocation;
	FVector CurrentLocation;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Timer
	FTimerHandle DisappearTimerHandle;
	void Disappear();
	UPROPERTY(EditAnywhere);
	float DisappearDelay;

};
