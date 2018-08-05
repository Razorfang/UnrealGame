// Fill out your copyright notice in the Description page of Project Settings.

#include "SquareGridTile.h"


// Sets default values
ASquareGridTile::ASquareGridTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASquareGridTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASquareGridTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


float ASquareGridTile::GetTileLength() const
{
	return TileLength;
}
float ASquareGridTile::GetTileWidth() const
{
	return TileWidth;
}

float ASquareGridTile::GetTileHeight() const
{
	return TileHeight;
}


void ASquareGridTile::SetTileLength(float Length)
{
	TileLength = Length;
}
void ASquareGridTile::SetTileWidth(float Width)
{
	TileWidth = Width;
}
void ASquareGridTile::SetTileHeight(float Height)
{
	TileHeight = Height;
}