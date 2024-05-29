// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructionRobot.h"


AConstructionRobot::AConstructionRobot()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AConstructionRobot::BeginPlay()
{
	Super::BeginPlay();
	
}

void AConstructionRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToTarget(DeltaTime);
}

void AConstructionRobot::MoveToTarget(const float DeltaTime)
{
	FVector NewTargetLocation = TargetLocation;
	NewTargetLocation.Z = NewTargetLocation.Z+75;
	const FVector NewLocation = FMath::VInterpTo(GetActorLocation(), NewTargetLocation, DeltaTime, 1.f);
	SetActorLocation(NewLocation);

	if (FVector::Dist(GetActorLocation(), TargetLocation) < 1.f)
	{
		//TargetLocation = HarbourLocation;
	}
}


