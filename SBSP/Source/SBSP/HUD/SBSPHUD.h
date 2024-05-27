// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SBSPHUD.generated.h"

class USimOverlay;

UCLASS()
class SBSP_API ASBSPHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASBSPHUD();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USimOverlay> SimOverlayClass;

private:
	UPROPERTY()
	USimOverlay* SimOverlayRef;

};
