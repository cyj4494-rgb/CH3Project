// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"
#include "engine/world.h"
#include "SpartaGameStateBase.h"

ACoinItem::ACoinItem() {
	PointValue = 0;
	ItemType = "DefalutCoin";
}

void ACoinItem::ActivateItem(AActor* Activator) {
	if (Activator && Activator->ActorHasTag("Player")) {
		if (UWorld* World = GetWorld()) {
			if (ASpartaGameStateBase* GameState = World->GetGameState<ASpartaGameStateBase>()) {
				GameState->AddScore(PointValue);
			}
		}
		DestroyItem();
	}
}