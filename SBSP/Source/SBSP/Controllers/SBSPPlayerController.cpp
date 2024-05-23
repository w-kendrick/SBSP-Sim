// Fill out your copyright notice in the Description page of Project Settings.


#include "SBSPPlayerController.h"


// Sets default values
ASBSPPlayerController::ASBSPPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASBSPPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBSPPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

