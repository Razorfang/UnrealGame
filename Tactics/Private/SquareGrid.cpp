// Fill out your copyright notice in the Description page of Project Settings.

#include "SquareGrid.h"

// Sets default values
ASquareGrid::ASquareGrid()
{
	/*Set this grid's type, changing it from UNKNOWN to SQUARE*/
	GridType = EGridType::ESquare;

	/* Each tile has a length and width of 1 to start*/
	TileWidth = 1.0f;
	TileLength = 1.0f;
	TileHeight = 0.0f;

	/* Record that the grid is 1x1 */
	SizeX = 1;
	SizeY = 1;
	SizeZ = 1; //2D grids, such as an 8x8 chess board, have a height of 1 in this system

	/*Resize the grid appropriately*/
	Grid.Init(NULL_VECTOR, 1);

	/*Set the cell mesh here. For now, we will use the Plane mesh.*/
	GridMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CellAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane"));
	if (CellAsset.Succeeded())
	{
		GridMesh->SetStaticMesh(CellAsset.Object);

		/*Set the mesh location so that it is located at the only cell
		TODO: Check if we want the point to be the middle or the bottom-left corner 
		This is just a test*/
		
	}
}

int ASquareGrid::CoordToIndex(int x, int y, int z) const
{
	/* If you need to understand this equation, please email me and I'll send a scan of my equations */
	return (SizeX * SizeY) * z + (SizeY) * x + y;
}

void ASquareGrid::AddTile(int x, int y, int z)
{
	/* TODO */
}

void ASquareGrid::RemoveTile(int x, int y, int z)
{
	/* If the tile is at the end, chop it off and resize the array*/
	if (CoordToIndex(x,y,z) == Grid.Num() - 1)
	{
		Grid.Pop(); /* TODO: Check that this does what I think it does, which is remove the last element and resize the array*/

		/* If we have a one-dimensional line grid with no height, then we need to resize now. 
		Unless it's the last element, in which case we wanted to delete the grid class */
		check((Grid.Num() > 0) && "You are trying to remove the last tile. Please just delete the entire grid");

	}

	/* Otherwise, replace the tile with a null vector */
	else 
	{
		Grid.Insert(NULL_VECTOR, CoordToIndex(x, y, z)); /* TODO: Check that this overwrites, and doesn't just do nothing */
	}

	/* There are many cases where we want to resize the grid depending on what we deleted. 
	TODO: Check for all possible cases */
}

int ASquareGrid::GetTileWidth() const {return TileWidth;}
int ASquareGrid::GetTileLength() const{return TileLength;}
int ASquareGrid::GetTileHeight() const {return TileHeight;}

void ASquareGrid::SetTileWidth(float NewWidth)
{
	check((NewWidth > 0) && "Do not set the tile width to that! Delete the grid instead");
	TileWidth = NewWidth;

	float OriginY = GetGridOrigin().Y;

	/* TODO: Change the Y-value of all points in the grid */

	/* TODO: Correct the appearance of the grid mesh */
}

void ASquareGrid::SetTileLength(float NewLength)
{
	check((NewLength > 0) && "Do not set the tile length to that! Delete the grid instead");
	TileLength = NewLength;

	/* TODO: Change the X-value of all points in the grid */

	/* TODO: Correct the appearance of the grid mesh */
}

void ASquareGrid::SetTileHeight(float NewHeight)
{
	TileHeight = NewHeight;

	/* TODO: Change the Z-value of all points in the grid */

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