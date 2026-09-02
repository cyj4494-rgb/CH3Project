// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingMineItem.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

AMovingMineItem::AMovingMineItem() {
	ExplosionDamage = 30.0f;
	ExplosionDelay = 5.0f;
	ExplosionRadius = 300.0f;
	ItemType = "MovingMine";
	bHasExploded = false;

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(300.0f);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);

}

void AMovingMineItem::ActivateItem(AActor* Activator) {

	if (bHasExploded) return;
	Super::ActivateItem(Activator);

	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,
		&AMovingMineItem::Explode,
		ExplosionDelay,
		false);

	bHasExploded = true;

}