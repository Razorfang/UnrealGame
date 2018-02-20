// Fill out your copyright notice in the Description page of Project Settings.

#include "Grid.h"

AGrid::AGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//We don't yet know what type of grid this is. This will be changed by the subclasses
	GridType = EGridType::EUnknown;
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

