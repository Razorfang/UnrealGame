// Fill out your copyright notice in the Description page of Project Settings.

#include "SquareGrid.h"

// Sets default values
ASquareGrid::ASquareGrid()
{
	/*Set this grid's type, changing it from UNKNOWN to SQUARE*/
	GridType = EGridType::ESquare;

	//Set up the grid default size, a 1x1 grid
	TileWidth = 1;
	TileLength = 1;
	TileHeight = 0;

	/*Resize the grid appropriately*/
	Grid.Init(NULL_VECTOR, 1);
}

void ASquareGrid::AddTile(int x, int y, int z)
{
	/* TODO */
}

void ASquareGrid::RemoveTile(int x, int y, int z)
{
	/* TODO */
}

int ASquareGrid::GetTileWidth() const {return TileWidth;}
int ASquareGrid::GetTileLength() const{return TileLength;}
int ASquareGrid::GetTileHeight() const {return TileHeight;}

void ASquareGrid::SetTileWidth(float NewWidth)
{
	check((NewWidth > 0) && "Do not set the width to that! Delete the grid instead");
	TileWidth = NewWidth;

	float OriginY = GetGridOrigin().Y;

	/* Change the Y-value of all points in the grid */

	/* TODO: Correct the appearance of the grid mesh */
}

void ASquareGrid::SetTileLength(float NewLength)
{
	check((NewLength > 0) && "Do not set the length to that! Delete the grid instead");
	TileLength = NewLength;

	/* Change the X-value of all points in the grid */

	/* TODO: Correct the appearance of the grid mesh */
}

void ASquareGrid::SetTileHeight(float NewHeight)
{
	TileHeight = NewHeight;

	/* Change the Z-value of all points in the grid */

	/* TODO: Correct the appearance of the grid mesh */
}

int ASquareGrid::GetSizeX() const { return SizeX; }
int ASquareGrid::GetSizeY() const { return SizeY; }
int ASquareGrid::GetSizeZ() const { return SizeZ; }

void ASquareGrid::SetSizeX(float NewWidth)
{
	/* TODO: Resize the grid by adding and removing vectors from the grid array */
}

void ASquareGrid::SetSizeY(float NewLength)
{
	/* TODO */
}

void ASquareGrid::SetSizeZ(float NewHeight)
{
	/* TODO */
}