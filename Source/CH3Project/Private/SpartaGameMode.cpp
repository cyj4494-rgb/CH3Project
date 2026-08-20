// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameMode.h"
#include "SpartaCharacter.h"

ASpartaGameMode::ASpartaGameMode() {

	DefaultPawnClass = ASpartaCharacter::StaticClass();
}
