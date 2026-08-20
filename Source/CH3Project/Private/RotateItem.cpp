// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateItem.h"

// Sets default values
ARotateItem::ARotateItem()
{	

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(RootScene);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotationSpeed = 200.0f;

}

// Called when the game starts or when spawned
void ARotateItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotateItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FMath::IsNearlyZero(RotationSpeed)) {
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}
}

