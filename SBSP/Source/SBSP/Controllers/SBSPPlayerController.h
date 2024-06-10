// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SBSPPlayerController.generated.h"

class ASBSPHUD;

UCLASS()
class SBSP_API ASBSPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASBSPPlayerController();

protected:
	virtual void BeginPlay() override;

	


private:
	UPROPERTY()
	ASBSPHUD* SBSPHUD;

};
