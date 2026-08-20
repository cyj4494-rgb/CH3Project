// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CH3PROJECT_API IItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//지회 힐링 코인
	//진입 이탈
	virtual void OnItemOverlap(AActor* OverlapActor) = 0; //0을 붙이면 반드시 오버라이딩 해야함 ( 순수 가상함수 )
	virtual void OnItemEndOverlap(AActor* overlapActor) = 0;
	virtual void ActivateItem(AActor* Activator) = 0;
	virtual FName GetItemType() const = 0; // string대신 FName 쓰는 이유 string은 무거워서 
};
