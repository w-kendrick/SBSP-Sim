// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceStructure.generated.h"

UCLASS()
class SBSP_API ASpaceStructure : public AActor
{
	GENERATED_BODY()

public:
	ASpaceStructure();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int BigHexagonRadius = 2; //Radius in number of tiles
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TileOffset = 5.f; //Size of gap between tiles.

public:
	virtual void Tick(float DeltaTime) override;
};
