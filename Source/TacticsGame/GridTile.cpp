// Fill out your copyright notice in the Description page of Project Settings.

#include "GridTile.h"


// Sets default values
AGridTile::AGridTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* All tiles begin un-highlighted */
	IsHighlighted = false;

}

// Called when the game starts or when spawned
void AGridTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FVector AGridTile::GetWorldLocation() const
{
	return WorldLocation;
}

UStaticMeshComponent* AGridTile::GetTileMesh() const
{
	return TileMesh;
}

void AGridTile::SetTileMesh(UStaticMeshComponent* NewTileMesh)
{
	TileMesh = NewTileMesh;
}

bool AGridTile::GetIsHighlighted() const
{
	return IsHighlighted;
}

void AGridTile::SetIsHighlighted(bool HighlightedState)
{
	IsHighlighted = HighlightedState;

}

