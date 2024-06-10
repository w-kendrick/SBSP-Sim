// Fill out your copyright notice in the Description page of Project Settings.


#include "SBSPPlayerController.h"

#include "SBSP/HUD/SBSPHUD.h"


// Sets default values
ASBSPPlayerController::ASBSPPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASBSPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const FInputModeGameAndUI InputModeGameAndUI = FInputModeGameAndUI();
	SetInputMode(InputModeGameAndUI);
	SetShowMouseCursor(true);

	if (ASBSPHUD* HUD = Cast<ASBSPHUD>(GetHUD()))
	{
		SBSPHUD = HUD;
		SBSPHUD->AddSimOverlay();
	}
}


