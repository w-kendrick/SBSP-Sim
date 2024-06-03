// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGrid.h"

#include "SAdvancedTransformInputBox.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SBSP/HexGrid/HexTile.h"
#include "SBSP/Robots/ConstructionRobot.h"


AHexGrid::AHexGrid()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHexGrid::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ConstructionRobot &&
	ConstructionRobot->GetRobotState() == ERobotState::Free
	&& !TileLocations.IsEmpty())
	{
		FVector Location;
		TileLocations.Dequeue(Location);
		ConstructionRobot->PlaceTileAtLocation(Location);
	}
}

void AHexGrid::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnRobot();
	LongRadius = GetMeshRadius();
	ConstructHexagon();
}

#pragma region Hex Tiles

void AHexGrid::ConstructHexagon()
{
	const float Sqrt3 = UKismetMathLibrary::Sqrt(3);
	FVector CurrentPoint = GetActorLocation();

	TArray<FVector> SpawnScheme = {
		FVector(1.5f, -Sqrt3*0.5f, 0.0f),	//DR
		FVector(0.f, -Sqrt3, 0.f),			//DX
		FVector(-1.5f, -Sqrt3*0.5f, 0.f),	//DL
		FVector(-1.5f, Sqrt3*0.5f, 0.f),	//UL
		FVector(0.f, Sqrt3, 0.f),			//UX
		FVector(1.5f, Sqrt3*0.5f, 0.f),	//UR
	};
	
	const float HexSide = LongRadius + TileSpacing;
	const int NumSpawns = SpawnScheme.Num();
	
	for (int mult = 0; mult <= BigHexagonRadius; mult++)
	{
		int hn = 0;
		for (int j = 0; j < NumSpawns; j++)
		{
			for (int i = 0; i < mult; i++, hn++)
			{
				const FVector Location = FVector(CurrentPoint.X, CurrentPoint.Y, CurrentPoint.Z);
				TileLocations.Enqueue(Location);
				CurrentPoint += (SpawnScheme[j]*HexSide);
			}
			if (j==4)
			{
				const FVector Location = FVector(CurrentPoint.X, CurrentPoint.Y, CurrentPoint.Z);
				TileLocations.Enqueue(Location);
				CurrentPoint += (SpawnScheme[j]*HexSide);
				hn++;
				if (mult==BigHexagonRadius) break;
			}
		}
		
	}
}

void AHexGrid::CreateTile(const FVector& Location, float Scale)
{
	if (!HexTileClass) return;

	FVector RobotLocation = Location;
	RobotLocation.Z = RobotLocation.Z+75;
	
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

#pragma endregion 

#pragma region Robots

void AHexGrid::SpawnRobot()
{
	if (!ConstructionRobotClass || !HexTileMesh) return;
	
	const FVector Location = GetActorLocation()+(HexTileMesh->GetBoundingBox().Max.Z*TileScale);
	
	if (AConstructionRobot* SpawnedRobot = Cast<AConstructionRobot>(GetWorld()->SpawnActor(
		ConstructionRobotClass,
		&Location
		)))
	{
		ConstructionRobot = SpawnedRobot;
		ConstructionRobot->SetHarbourLocation(Location);
		ConstructionRobot->SetHexTileClass(HexTileClass);
	}
}

#pragma endregion 
