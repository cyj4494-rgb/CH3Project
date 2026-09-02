// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowingItem.h"
#include "SpartaCharacter.h"

ASlowingItem::ASlowingItem() {
	ItemType = "Slowing";
}

void ASlowingItem::ActivateItem(AActor* Activator) {

	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player")) {

		if (ASpartaCharacter* PlayerCharacter = Cast<ASpartaCharacter>(Activator))
		{
			PlayerCharacter->ApplySlow();
		}
		DestroyItem();
	}
}