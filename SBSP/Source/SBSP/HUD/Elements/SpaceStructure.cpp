// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceStructure.h"


ASpaceStructure::ASpaceStructure()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceStructure::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpaceStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

