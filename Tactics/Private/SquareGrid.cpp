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
	TileHeight = 1.0f;

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
	/* Check if we have something at that spot. This can be something, or a null vector.
	If nothing is at that location, add the tile there and update everything as needed
	If a null vector is there, overwrite it
	If a non-null vector is there, we will always overwrite it

	In all cases
	*/

	FVector GridOrigin = GetGridOrigin();
	FVector NewTilePosition(GridOrigin.X + GetTileLength() * x, GridOrigin.Y + GetTileWidth() * y, GridOrigin.Z + GetTileHeight() * z);

	int index = CoordToIndex(x, y, z);
	Grid.Insert(NewTilePosition, index); //Does this resize? Does this overwrite?
	UpdateAllSizes();
}

void ASquareGrid::RemoveTile(int x, int y, int z)
{
	/* TODO */
}

float ASquareGrid::GetTileWidth() const {return TileWidth;}
float ASquareGrid::GetTileLength() const{return TileLength;}
float ASquareGrid::GetTileHeight() const {return TileHeight;}

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

void ASquareGrid::SetSizeX(int NewSizeX)
{
	/* TODO: Resize the grid by adding and removing vectors from the grid array */
}

void ASquareGrid::SetSizeY(int NewSizeY)
{
	/* TODO */
}

void ASquareGrid::SetSizeZ(int NewSizeZ)
{
	/* TODO */
}

void ASquareGrid::UpdateSizeX()
{
	//Find how many cells are in the X dimension. Done by checking all in first X row
	float LargestCoordInX = GetGridOrigin().X;

	//Iterate through all of the locations, checking for the largest X
	for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i].X > LargestCoordInX)
		{
			LargestCoordInX = Grid[i].X;
		}
	}

	float LengthX = LargestCoordInX - GetGridOrigin().X;

	//Update accordingly. Also it's probably a good idea to check for rounding errors here, which is why we're using round
	SetSizeX(round(LengthX / GetTileLength()));
	
}

void ASquareGrid::UpdateSizeY()
{
	//Find how many cells are in the X dimension. Done by checking all in first X row
	float LargestCoordInY = GetGridOrigin().Y;

	//Iterate through all of the locations, checking for the largest X
	for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i].Y > LargestCoordInY)
		{
			LargestCoordInY = Grid[i].Y;
		}
	}

	float WidthY = LargestCoordInY - GetGridOrigin().Y;

	//Update accordingly. Also it's probably a good idea to check for rounding errors here, which is why we're using round
	SetSizeY(round(WidthY / GetTileWidth()));
}

void ASquareGrid::UpdateSizeZ()
{
	//Find how many cells are in the X dimension. Done by checking all in first X row
	float LargestCoordInZ = GetGridOrigin().Z;

	//Iterate through all of the locations, checking for the largest X
	for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i].Z > LargestCoordInZ)
		{
			LargestCoordInZ = Grid[i].Z;
		}
	}

	float HeightZ = LargestCoordInZ - GetGridOrigin().Z;

	//Update accordingly. Also it's probably a good idea to check for rounding errors here, which is why we're using round
	SetSizeZ(round(HeightZ / GetTileHeight()));
}

void ASquareGrid::UpdateAllSizes()
{
	UpdateSizeX();
	UpdateSizeY();
	UpdateSizeZ();
}