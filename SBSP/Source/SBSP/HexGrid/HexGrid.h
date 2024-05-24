// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ChildActorComponent.h"
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
	virtual void BeginPlay() override;

	virtual void ConstructTiles();
	virtual void ConstructHexagon();

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int BigHexagonRadius = 2; //Radius in number of tiles
	
	
private:
	UPROPERTY()
	UChildActorComponent* ChildActorComponent;

	UPROPERTY()
	TArray<AHexTile*> HexTiles;
	
	float LongRadius;

	void CreateTile(float XLoc, float YLoc, float ZLoc, float Scale);

	float GetMeshRadius() const;
	float CalcYTransformLocation(const int Index) const;
	float CalcXTransformLocation(const int Index);

	bool bHexFlipFlop = true;
	float GetRowOffset();
};

