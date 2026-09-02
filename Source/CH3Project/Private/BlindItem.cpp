// Fill out your copyright notice in the Description page of Project Settings.


#include "BlindItem.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"

ABlindItem::ABlindItem()
{
	ItemType = "Blind";
}

void ABlindItem::ActivateItem(AActor* Activator) {
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player")) {

		if (ASpartaCharacter* PlayerCharacter = Cast<ASpartaCharacter>(Activator))
		{
			if (ASpartaPlayerController* PlayerController =
				Cast<ASpartaPlayerController>(PlayerCharacter->GetController()))
			{
				if (UUserWidget* HUDWidget = PlayerController->GetHUDWidget())
				{
					UFunction* PlayBlindFunction =
						HUDWidget->FindFunction(FName("PlayBlindAnim"));

					if (PlayBlindFunction)
					{
						HUDWidget->ProcessEvent(PlayBlindFunction, nullptr);
					}

				}
			}
		}
		DestroyItem();
	}
}