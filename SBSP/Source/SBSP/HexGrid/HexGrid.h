// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGrid.generated.h"

class AHexTile;

UCLASS()
class SBSP_API AHexGrid : public AActor
{
	GENERATED_BODY()

public:
	AHexGrid();

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHexTile> HexTileClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* HexTileMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TileOffset = 5.f; //Size of gap between tiles.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TileScale = 1.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int GridHeight = 10;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int GridWidth = 10;
	
	
private:

};

