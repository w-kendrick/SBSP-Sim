// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConstructionRobot.generated.h"

class AHexTile;

UCLASS()
class SBSP_API AConstructionRobot : public AActor
{
	GENERATED_BODY()

public:
	AConstructionRobot();

	virtual void Tick(float DeltaTime) override;

	
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* RobotMesh;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHexTile> HexTileClass;

private:
	bool bIsCarryingTile;

	FVector HarbourLocation;
	FVector TargetLocation;
	void MoveToTarget(float DeltaTime);

public:
	FORCEINLINE void SetHexTileClass(TSubclassOf<AHexTile> InHexTileClass) { HexTileClass = InHexTileClass; }
	FORCEINLINE void SetHarbourLocation(const FVector& Location) { HarbourLocation = Location; }
	FORCEINLINE void SetTargetLocation(const FVector& Location) { TargetLocation = Location; }
};
