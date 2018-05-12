// Fill out your copyright notice in the Description page of Project Settings.

#include "SquareGrid.h"

/* TODO: Should we trim NULL_VECTORS from the end of the grid, since it kind of goes against our system? */


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

	UE_LOG(LogTemp, Warning, TEXT("The origin is %f,%f,%f"), GetGridOrigin().X, GetGridOrigin().Y, GetGridOrigin().Z);

	/*Resize the grid appropriately*/
	Grid.Init(GetGridOrigin(), 1);

	/*Set the cell mesh here. For now, we will use the Plane mesh.*/
	//GridMesh->SetupAttachment(RootComponent);
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
	UE_LOG(LogTemp, Warning, TEXT("%d,%d,%d maps to %d"), x, y, z, (SizeX * SizeY) * z + (SizeX)* y + x);
	/* If you need to understand this equation, please email me and I'll send a scan of my equations */
	return (SizeX * SizeY) * z + (SizeX)* y + x;
}

void ASquareGrid::AddTile(int x, int y, int z)
{
	FVector GridOrigin = GetGridOrigin();
	FVector NewTile(GridOrigin.X + GetTileLength() * x, GridOrigin.Y + GetTileWidth() * y, GridOrigin.Z + GetTileHeight() * z);
	UE_LOG(LogTemp, Warning, TEXT("New Tile Location: %f, %f, %f"), NewTile.X, NewTile.Y, NewTile.Z);

	int index = CoordToIndex(x, y, z);

	//If we're adding a tile outside the current grid, we add the new vector, then fill in the gaps with null vectors
	if (index >= Grid.Num())
	{
		//Add more null vectors as needed
		for (int i = 0; i < (index - Grid.Num()); i++)
		{
			Grid.Add(NULL_VECTOR);
		}
		Grid.Add(NewTile);

		UE_LOG(LogTemp, Warning, TEXT("Adding tile to the end of the grid and filling in space"));
	}

	//If there is a null vector there, then we overwrite it
	else if (Grid[index] == NULL_VECTOR)
	{
		Grid.Insert(NewTile, index); //Does this resize? Does this overwrite? It probably overwrites and probably doesn't resize

		UE_LOG(LogTemp, Warning, TEXT("Overwriting null vector with new tile"));

	}

	else
	{
		//If there is another tile at the index, then we should leave it be
		UE_LOG(LogTemp, Warning, TEXT("Valid tile at that index, no reason to add"));
	}

	UpdateAllSizes(); //While it may not be necessary to update all dimensions after only one tile is added, I'm not taking any chances
}

void ASquareGrid::AddNullTile(int x, int y, int z)
{

	int index = CoordToIndex(x, y, z);

	//If we're adding a tile outside the current grid, we add a bunch of null vectors
	if (index >= Grid.Num())
	{
		//Add more null vectors as needed
		for (int i = 0; i < (index - Grid.Num() + 1); i++)
		{
			Grid.Add(NULL_VECTOR);
		}
	}

	//If there is an existing tile there, we overwrite it
	else if (Grid[index] != NULL_VECTOR)
	{
		Grid.Insert(NULL_VECTOR, index); //Does this resize? Does this overwrite? It probably overwrites and probably doesn't resize
	}

	else
	{
		//If there is a null tile there, we do nothing
	}

	UpdateAllSizes(); //While it may not be necessary to update all dimensions after only one tile is added, I'm not taking any chances
}


void ASquareGrid::RemoveTile(int x, int y, int z)
{
	int Index = CoordToIndex(x, y, z);

	//If the tile is is within bounds, remove it and resize the grid (regardless of if it is null or not)
	if (Index < Grid.Num())
	{
		//We do this by swapping repeatedly, then popping
		while (Index < Grid.Num() - 1)
		{
			Grid.Swap(Index, Index + 1);
			Index++;
		}
		Grid.Pop();

	}
	//If the tile is outside the grid bounds, do nothing
	else
	{

	}

	UpdateAllSizes();
}

void ASquareGrid::NullifyTile(int x, int y, int z)
{
	int Index = CoordToIndex(x, y, z);

	/* Within grid bounds */
	if (Index < Grid.Num())
	{
		//If the tile is non-null, turn it null
		if (Grid[Index] != NULL_VECTOR)
		{
			Grid.Insert(NULL_VECTOR, Index);
		}

		//If the tile is null, do nothing
	}

	//If outside the bounds of the grid, throw a warning, saying to use AddNull instead (TODO)

	UpdateAllSizes();
}

float ASquareGrid::GetTileWidth() const { return TileWidth; }
float ASquareGrid::GetTileLength() const { return TileLength; }
float ASquareGrid::GetTileHeight() const { return TileHeight; }

void ASquareGrid::SetTileWidth(float NewWidth)
{
	check((NewWidth > 0) && "Do not set the tile width to that! Delete the grid instead");
	TileWidth = NewWidth;

	float OriginY = GetGridOrigin().Y;

	/* Change the Y-value of all points in the grid */
	for (int i = 0; i < Grid.Num(); i++)
	{
		Grid[i].Y = NewWidth;
	}

	/* TODO: Correct the appearance of the grid mesh */
}

void ASquareGrid::SetTileLength(float NewLength)
{
	check((NewLength > 0) && "Do not set the tile length to that! Delete the grid instead");
	TileLength = NewLength;

	/* Change the X-value of all points in the grid */
	for (int i = 0; i < Grid.Num(); i++)
	{
		Grid[i].X = NewLength;
	}

	/* TODO: Correct the appearance of the grid mesh */
}

void ASquareGrid::SetTileHeight(float NewHeight)
{
	TileHeight = NewHeight;

	/* Change the Z-value of all points in the grid */
	for (int i = 0; i < Grid.Num(); i++)
	{
		Grid[i].Z = NewHeight;
	}

	/* TODO: Correct the appearance of the grid mesh */
}

int ASquareGrid::GetSizeX() const { return SizeX; }
int ASquareGrid::GetSizeY() const { return SizeY; }
int ASquareGrid::GetSizeZ() const { return SizeZ; }

void ASquareGrid::SetSizeX(int NewSizeX)
{
	/* TODO */
}

void ASquareGrid::SetSizeY(int NewSizeY)
{
	/* TODO: Resize the grid by adding and removing vectors from the grid array */

	//Shrinking
	if (NewSizeY < SizeY)
	{
		//Removing elements
	}

	//Growing
	else if (NewSizeY > SizeY)
	{
		//Adding more null vectors

	}

	//Else, the sizes are the same, and we do nothing

	SizeY = NewSizeY;



	//Since updating the sizes is already done by the AddTile function, we don't need to do it here
}

void ASquareGrid::SetSizeZ(int NewSizeZ)
{
	SizeZ = NewSizeZ;
	/* TODO */
}

void ASquareGrid::UpdateSizeX()
{

	UE_LOG(LogTemp, Warning, TEXT("Updating Size X"));

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
	SetSizeX(round(LengthX / GetTileLength()) + 1);

	UE_LOG(LogTemp, Warning, TEXT("New Size X is %d"), GetSizeX());

}

void ASquareGrid::UpdateSizeY()
{
	UE_LOG(LogTemp, Warning, TEXT("Updating Size Y"));

	//Find how many cells are in the X dimension. Done by checking all in first X row
	float LargestCoordInY = GetGridOrigin().Y;

	//Iterate through all of the locations, checking for the largest X
	for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i].Y > LargestCoordInY)
		{
			UE_LOG(LogTemp, Warning, TEXT("Grid[i] = %f"), Grid[i].Y);
			LargestCoordInY = Grid[i].Y;
		}
	}

	float WidthY = LargestCoordInY - GetGridOrigin().Y;
	UE_LOG(LogTemp, Warning, TEXT("GetGridOrigin().Y = %f"), GetGridOrigin().Y);
	UE_LOG(LogTemp, Warning, TEXT("WidthY = %f"), WidthY);
	UE_LOG(LogTemp, Warning, TEXT("Tile Width = %f"), GetTileWidth());
	//Update accordingly. Also it's probably a good idea to check for rounding errors here, which is why we're using round
	SetSizeY(round(WidthY / GetTileWidth()) + 1);

	UE_LOG(LogTemp, Warning, TEXT("New Size Y is %d"), GetSizeY());
}

void ASquareGrid::UpdateSizeZ()
{

	UE_LOG(LogTemp, Warning, TEXT("Updating Size Z"));

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
	SetSizeZ(round(HeightZ / GetTileHeight()) + 1);

	UE_LOG(LogTemp, Warning, TEXT("New Size Z is %d"), GetSizeZ());

}

void ASquareGrid::UpdateAllSizes()
{
	UpdateSizeX();
	UpdateSizeY();
	UpdateSizeZ();
}