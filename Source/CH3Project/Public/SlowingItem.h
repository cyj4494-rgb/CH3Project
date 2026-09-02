// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SlowingItem.generated.h"

UCLASS()
class CH3PROJECT_API ASlowingItem : public ABaseItem
{
	GENERATED_BODY()

	
	
public:
	ASlowingItem();

	void ActivateItem(AActor* Activator);

};
