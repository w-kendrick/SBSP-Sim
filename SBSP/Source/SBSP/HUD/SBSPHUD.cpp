// Fill out your copyright notice in the Description page of Project Settings.


#include "SBSPHUD.h"

#include "SimOverlay.h"


ASBSPHUD::ASBSPHUD()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASBSPHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ASBSPHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASBSPHUD::AddSimOverlay()
{
	if (SimOverlayClass)
	{
		SimOverlayRef = CreateWidget<USimOverlay>(GetOwningPlayerController(), SimOverlayClass);
		if (SimOverlayRef)
		{
			SimOverlayRef->AddToViewport();
		}
	}
}

