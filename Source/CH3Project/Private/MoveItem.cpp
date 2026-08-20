// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveItem.h"

// Sets default values
AMoveItem::AMoveItem()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(RootScene);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 200.0f;
	MaxRange = 1000.0f;
	MoveCount = 0.0f;
	Flow_Time = 0.0f;
	X_Y_Z = 0;
}

// Called when the game starts or when spawned
void AMoveItem::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();

	GetWorld()->GetTimerManager().SetTimer(
		DisappearTimerHandle,
		this,
		&AMoveItem::Disappear,
		DisappearDelay,
		false
	);
}

void AMoveItem::Disappear() {
	Destroy();
}

// Called every frame
void AMoveItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//벡터
	CurrentLocation = GetActorLocation();
	Flow_Time += DeltaTime;
	float offset = FMath::Sin(Flow_Time * MoveSpeed) * MaxRange;
	switch (X_Y_Z) {
	case 0:
		SetActorLocation(StartLocation + FVector(offset, 0.0f, 0.0f));
		break;
	case 1:
		SetActorLocation(StartLocation + FVector(0.0f, offset, 0.0f));
		break;
	case 2:
		SetActorLocation(StartLocation + FVector(0.0f, 0.0f, offset));
		break;
	}
	
}

