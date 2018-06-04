// Fill out your copyright notice in the Description page of Project Settings.

#include "Grid.h"

AGrid::AGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/* We don't yet know what type of grid this is. This will be changed by the subclasses */
	GridType = EGridType::EUnknown;

	/* This component will be at the top of our component heirarchy */
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	//Create the static mesh component
	//GridMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridMesh"));

	/* Set mobility to stationary for efficient lighting */
	//GridMesh->SetMobility(EComponentMobility::Stationary);

	//Base other stuff around this component. Not needed for our example, but we may come back to this
	//RootComponent = GridMesh;

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

EGridType AGrid::GetGridType() const
{
	return GridType;
}

FVector AGrid::GetGridOrigin() const
{
	return GetActorLocation(); //This returns the rootcomponent's location relative to the centre of the actor, not our world location
							   //return GridMesh->GetComponentLocation();
}