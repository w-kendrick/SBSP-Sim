// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGrid.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SBSP/HexGrid/HexTile.h"


AHexGrid::AHexGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActorComponent"));
	ChildActorComponent->SetChildActorClass(AHexTile::StaticClass());
}

void AHexGrid::BeginPlay()
{
	Super::BeginPlay();

	Radius = GetMeshRadius();
	ConstructTiles();
}

void AHexGrid::ConstructTiles()
{
	if (!ChildActorComponent) return;
	
	for (int i=0; i < GridHeight; i++)
	{
		const float YLoc = CalcYTransformLocation(i);
		for (int j=0; j < GridWidth; j++)
		{
			CreateTile(CalcXTransformLocation(j), YLoc, 0.f, TileScale);
		}
		bHexFlipFlop = !bHexFlipFlop;
	}
}

void AHexGrid::CreateTile(float XLoc, float YLoc, float ZLoc, float Scale)
{
	const FVector Location = FVector(XLoc, YLoc, ZLoc);

	if (AHexTile* SpawnedTile = Cast<AHexTile>(GetWorld()->SpawnActor(
		HexTileClass,
		&Location
	)))
	{
		HexTiles.Add(SpawnedTile);
		SpawnedTile->SetActorScale3D(FVector::One()*TileScale);
	}
}

float AHexGrid::GetMeshRadius() const
{
	if (!HexTileMesh) return -1.f;
	const float MaxX = HexTileMesh->GetBoundingBox().Max.X;

	return TileScale*MaxX;
}

float AHexGrid::CalcYTransformLocation(const int Index) const
{
	const double HexEq = (Radius*2.0f)/UKismetMathLibrary::Sqrt(3);
	const float YLoc = HexEq*Index*1.5f;;
	const float Offset = TileOffset*Index;

	return YLoc + Offset;
}

float AHexGrid::CalcXTransformLocation(const int Index)
{
	return (Radius*2.f*Index)+(TileOffset*Index)+GetRowOffset();
}

float AHexGrid::GetRowOffset()
{
	if (bHexFlipFlop) return Radius*-1.f;
	return 0.f;
}


