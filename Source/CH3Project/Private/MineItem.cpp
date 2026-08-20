// Fill out your copyright notice in the Description page of Project Settings.


#include "MineItem.h"
#include "TimerManager.h"
#include "Components/SphereComponent.h"



AMineItem::AMineItem() {
	ExplosionDamage = 30.0f;
	ExplosionDelay = 5.0f;
	ExplosionRadius = 300.0f;
	ItemType = "Mine";

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(300.0f);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);

}


void AMineItem::ActivateItem(AActor* Activator) {
	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,
		&AMineItem::Explode,
		ExplosionDelay,
		false);
	
}

void AMineItem::Explode() {
	TArray<AActor*> OverlappingActors;
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{

		}
	}
	DestroyItem();
}