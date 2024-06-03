// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructionRobot.h"

#include "Kismet/KismetSystemLibrary.h"
#include "SBSP/HexGrid/HexTile.h"


AConstructionRobot::AConstructionRobot()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AConstructionRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToTarget(DeltaTime);
}

void AConstructionRobot::BeginPlay()
{
	Super::BeginPlay();
}

void AConstructionRobot::PlaceTileAtLocation(const FVector& Location)
{
	if (RobotState != ERobotState::Free) return;
	RobotState = ERobotState::MovingTile;
	TargetLocation = Location;
	UKismetSystemLibrary::PrintString(this, TargetLocation.ToString());
}

void AConstructionRobot::PlaceTile()
{
	if (!HexTileClass) return;
	
	if (AHexTile* SpawnedTile = Cast<AHexTile>(GetWorld()->SpawnActor(
		HexTileClass,
		&TargetLocation
	)))
	{
		RobotState = ERobotState::ReturningHome;
		TargetLocation = HarbourLocation;
		UKismetSystemLibrary::PrintString(this, "Placed Tile");
	}
}

void AConstructionRobot::MoveToTarget(const float DeltaTime)
{
	FVector NewTargetLocation = TargetLocation;
	NewTargetLocation.Z = NewTargetLocation.Z+75;
	const FVector NewLocation = FMath::VInterpTo(
		GetActorLocation(),
		NewTargetLocation,
		DeltaTime,
		RobotSpeed);
	SetActorLocation(NewLocation);
	
	if (RobotState == ERobotState::MovingTile &&
		FVector::DistXY(GetActorLocation(), TargetLocation) < 5.f)
	{
		UKismetSystemLibrary::PrintString(this, "Placing Tile");
		PlaceTile();
	}
	else if (RobotState == ERobotState::ReturningHome &&
		FVector::DistXY(GetActorLocation(), HarbourLocation) < 5.f)
	{
		UKismetSystemLibrary::PrintString(this, "Returned Home");
		RobotState = ERobotState::Free;
	}
}


