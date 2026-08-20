// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ABaseItem::OnItemOverlap(AActor* OverlapActor)
{
}

void ABaseItem::OnItemEndOverlap(AActor* overlapActor)
{
}

void ABaseItem::ActivateItem(AActor* Activator)
{
}

void ABaseItem::DestroyItem() {
	Destroy();
}

FName ABaseItem::GetItemType() const
{
	return ItemType;
}
