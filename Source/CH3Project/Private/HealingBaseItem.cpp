// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingBaseItem.h"

AHealingBaseItem::AHealingBaseItem() {
	HealAmount = 20.0f;
	ItemType = "Healing";
}

void AHealingBaseItem::ActivateItem(AActor* Activator) {
	Destroy();
}