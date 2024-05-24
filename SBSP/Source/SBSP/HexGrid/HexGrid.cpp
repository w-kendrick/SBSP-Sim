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

	LongRadius = GetMeshRadius();
	ConstructHexagon();
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

	const float HexSide = LongRadius+20;
	const int NumSpawns = SpawnScheme.Num();
	
	for (int mult = 0; mult <= BigHexagonRadius; mult++)
	{
		int hn = 0;
		for (int j = 0; j < NumSpawns; j++)
		{
			for (int i = 0; i < mult; i++, hn++)
			{
				CreateTile(CurrentPoint.X, CurrentPoint.Y, CurrentPoint.Z, 1.f);
				CurrentPoint += (SpawnScheme[j]*HexSide);
			}
			if (j==4)
			{
				CreateTile(CurrentPoint.X, CurrentPoint.Y, CurrentPoint.Z, 1.f);
				CurrentPoint += (SpawnScheme[j]*HexSide);
				hn++;
				if (mult==BigHexagonRadius) break;
			}
		}
		
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
	const double Apothem = (LongRadius*2.0f)/UKismetMathLibrary::Sqrt(3);
	const float YLoc = Apothem*Index*1.5f;
	const float Offset = TileOffset*Index;

	return YLoc + Offset;
}

float AHexGrid::CalcXTransformLocation(const int Index)
{
	return (LongRadius*2.f*Index)+(TileOffset*Index)+GetRowOffset();
}

float AHexGrid::GetRowOffset()
{
	if (bHexFlipFlop) return LongRadius*-1.f;
	return 0.f;
}


