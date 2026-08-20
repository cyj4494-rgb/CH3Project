// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"

ACoinItem::ACoinItem() {
	PointValue = 0;
	ItemType = "DefalutCoin";
}

void ACoinItem::ActivateItem(AActor* Activator) {
	if (Activator && Activator->ActorHasTag("Player")) {
		DestroyItem();
	}
}