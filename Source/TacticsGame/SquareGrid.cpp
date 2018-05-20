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
	SizeX = 0;
	SizeY = 0;
	SizeZ = 0; //2D grids, such as an 8x8 chess board, have a height of 1 in this system

	//UE_LOG(LogTemp, Warning, TEXT("The origin is %f,%f,%f"), GetGridOrigin().X, GetGridOrigin().Y, GetGridOrigin().Z);

	/*Set the cell mesh here. For now, we will use the Plane mesh.*/
	//GridMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CellAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane"));
	if (CellAsset.Succeeded())
	{
		GridMesh->SetStaticMesh(CellAsset.Object);

		/*Set the mesh location so that it is located at the only cell
		TODO: Check if we want the point to be the middle or the bottom-left corner
		This is just a test*/

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Square grid initialized. TW,TL,TH,SX,SY,SZ,origin: %f,%f,%f,%d,%d,%d,(%f %f %f)"), TileWidth, TileLength, TileHeight, SizeX, SizeY, SizeZ, GetGridOrigin().X, GetGridOrigin().Y, GetGridOrigin().Z));

		//Set the mobility of the grid to immoble
		GridMesh->SetMobility(EComponentMobility::Stationary);

	}
}

int ASquareGrid::CoordToIndex(int x, int y, int z) const
{

	/*If this vector falls outside the current grid, we need to get future sizes to update correctly
	This means doing some checking
	Although we need new sizes, we aren't updating them right now*/
	/*int newSizeX = SizeX;
	int newSizeY = SizeY;
	int newSizeZ = SizeZ;

	if (x >= SizeX) { newSizeX = x + 1; };
	if (y >= SizeY) { newSizeY = y + 1; };
	if (z >= SizeZ) { newSizeZ = z + 1; };

	UE_LOG(LogTemp, Warning, TEXT("%d,%d,%d maps to %d"), x, y, z, (newSizeX * newSizeY) * z + (newSizeX)* y + x);

	return (newSizeX * newSizeY) * z + (newSizeX)* y + x;*/

	//If the new coordinate exists outside the grid, then we need to check for that outside this function, not inside it.
	//Checking inside not only causes issues, but also goes against functional programming principles.

	/*UE_LOG(LogTemp, Warning, TEXT("%d,%d,%d maps to %d"), x, y, z, (SizeX * SizeY) * z + (SizeX)* y + x);

	return (SizeX * SizeY) * z + (SizeX)* y + x;*/

	return 0;

}


bool ASquareGrid::IsWithinBounds(int x, int y, int z) const
{
	if (x >= SizeX || y >= SizeY || z >= SizeZ)
	{
		return false;
	}

	return true;
}

FVector ASquareGrid::CoordToWorld(int x, int y, int z) const
{
	FVector GridOrigin = GetGridOrigin();
	FVector NewTile(GridOrigin.X + GetTileLength() * x, GridOrigin.Y + GetTileWidth() * y, GridOrigin.Z + GetTileHeight() * z);

	return NewTile;
}

void ASquareGrid::RecursiveSwap(int i)
{
	/*UE_LOG(LogTemp, Warning, TEXT("Grid[%d] is not NULL_VECTOR"), i);

	//Since CoordToIndex checks where the coordinate should be in the current grid, we can use it to detect where changes should happen
	int NewIndex = CoordToIndex(Grid[i].X, Grid[i].Y, Grid[i].Z);

	UE_LOG(LogTemp, Warning, TEXT("New index is %d"), NewIndex);

	//Swap elements
	Grid.Swap(i, NewIndex);

	//If grid[i] is NULL_VECTOR, or the newindex an oldindex are the same, we are done. Otherwise, we repeat this swapping with the thing we just swapped
	if ((Grid[i] != NULL_VECTOR) && (NewIndex != i))
	{
		RecursiveSwap(i);
	}*/
}

void ASquareGrid::InitTiles(int length, int width, int height)
{

	if (Grid.Num() == 0)
	{
		SizeX = length;
		SizeY = width;
		SizeZ = height;

		for (int z = 0; z < SizeZ; z++)
		{
			for (int y = 0; y < SizeY; y++)
			{
				for (int x = 0; x < SizeX; x++)
				{
					//We iterate through x first, then y, then z, so we append in the correct order
					Grid.Add(CoordToWorld(x, y, z));
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Please don't call this function if the grid is non-empty"));
	}

	//Check the grid itself
	UE_LOG(LogTemp, Warning, TEXT("After updating, the grid looks like: "));
	for (int i = 0; i < Grid.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grid[%d] = (%f, %f, %f)"), i, Grid[i].X, Grid[i].Y, Grid[i].Z);
	}
}

void ASquareGrid::AddTile(int x, int y, int z)
{
	FVector GridOrigin = GetGridOrigin();
	FVector NewTile = CoordToWorld(x, y, z);
	UE_LOG(LogTemp, Warning, TEXT("New Tile Location: %f, %f, %f"), NewTile.X, NewTile.Y, NewTile.Z);

	//If the grid is empty, then we add a bunch of null tiles appropriately
	if (Grid.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grid is empty. Populating now."));
		//i.e. we fill a grid with exactly the right number of null tiles minus one, then we add this to the end
		SizeX = x + 1;
		SizeY = y + 1;
		SizeZ = z + 1;

		for (int i = 0; i < (SizeX * SizeY * SizeZ) - 1; i++)
		{
			Grid.Add(NULL_VECTOR);
		}
		Grid.Add(NewTile);
	}

	//If adding a tile within bounds
	else if (IsWithinBounds(x, y, z))
	{
		UE_LOG(LogTemp, Warning, TEXT("Tile we want to add is within bounds"));

		//We can calculate the index better if we're in bounds
		int index = (SizeX * SizeY) * z + (SizeX)* y + x;

		//If it's NULL_VECTOR, overwrite it. 
		if (Grid[index] == NULL_VECTOR)
		{
			Grid[index] = NewTile;
		}

		//Otherwise, do nothing
	}

	//If it's outside of bounds, then we need to resize the grid accordingly. This is the tricky part
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tile we want to add is out of bounds. We will not implement this at this time"));

		//Readjust the grid sizes

		//Resize the grid appropriately

		//Move all tiles to new spots

		//Put new tile in its place

		//Remove unnecessary tiles from the end

	}

	/*
	else
	{
		//Tile outside of bounds, need to do complex stuff

		//Readjust the grid sizes
		if (x >= SizeX) { SizeX = x + 1; UE_LOG(LogTemp, Warning, TEXT("New SizeX is %d"), SizeX);}
		if (y >= SizeY) { SizeY = y + 1; UE_LOG(LogTemp, Warning, TEXT("New SizeY is %d"), SizeY);}
		if (z >= SizeZ) { SizeZ = z + 1; UE_LOG(LogTemp, Warning, TEXT("New SizeZ is %d"), SizeZ);}

		//Resize the grid appropriately, by adding more nulls on the end
		//Grid.SetNum(SizeX * SizeY * SizeZ);
		for (int j = Grid.Num(); j < (SizeX * SizeY * SizeZ); j++)
		{
			Grid.Add(NULL_VECTOR);
		}

		//Move all existing tiles to where their new spots are
		for (int i = 0; i < Grid.Num(); i++)
		{
			if (Grid[i] != NULL_VECTOR)
			{
				//Recursively swaps positions that are in the way of each other until the order is correct
				RecursiveSwap(i);
			}
		}

		//Put the new tile in its place
		Grid[index] = NewTile;

		//Remove unneessary tiles from the end
		int k = Grid.Num() - 1;
		while (Grid[k] == NULL_VECTOR)
		{
			Grid.RemoveAt(k);
			k = k - 1;
		}

		UE_LOG(LogTemp, Warning, TEXT("Adding tile to the end of the grid and filling in space"));

	}*/

	//Check the grid itself
	UE_LOG(LogTemp, Warning, TEXT("After updating, the grid looks like: "));
	for (int i = 0; i < Grid.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grid[%d] = (%f, %f, %f)"), i, Grid[i].X, Grid[i].Y, Grid[i].Z);
	}
}


void ASquareGrid::RemoveTile(int x, int y, int z)
{
	//NOTE: Removing a tile eliminates it from the grid completely. Nullifying a tile replaces a tile with NULL_VECTOR
	UE_LOG(LogTemp, Warning, TEXT("Removing tile at: %d, %d, %d"), x, y, z);
	/*int Index = CoordToIndex(x, y, z);

	//If the tile is is within bounds, and it isn't a NULL_VECTOR, remove it and resize the grid
	if (Index < Grid.Num())
	{
		if (Grid[Index] != NULL_VECTOR)
		{

			//Nullify the tile
			Grid[Index] = NULL_VECTOR;

			//Remove unneessary tiles from the end
			if (Grid.Num() > 0)
			{
				int k = Grid.Num() - 1;
				while (Grid.IsValidIndex(k) && Grid[k] == NULL_VECTOR)
				{
					Grid.RemoveAt(k);
					k = k - 1;
				}
			}

			//Move all existing tiles to where their new spots are
			for (int i = 0; i < Grid.Num(); i++)
			{
				if (Grid[i] != NULL_VECTOR)
				{
					//Recursively swaps positions that are in the way of each other until the order is correct
					RecursiveSwap(i);
				}
			}
		}

	}
	//If the tile is outside the grid bounds, do nothing
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing to remove here; this is outside the bounds of the grid or is a NULL_VECTOR"));
	}

	//Check the grid itself
	UE_LOG(LogTemp, Warning, TEXT("After updating, the grid looks like: "));
	for (int i = 0; i < Grid.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grid[%d] = (%f, %f, %f)"), i, Grid[i].X, Grid[i].Y, Grid[i].Z);
	}
	//Update the grid sizes
	UpdateAllSizes();*/


}

void ASquareGrid::NullifyTile(int x, int y, int z)
{
	//Nullifying certain tiles will cause the grid to be resized, similar to RemoveTile

	/*int Index = CoordToIndex(x, y, z);

	// Within grid bounds 
	if (Index < Grid.Num())
	{
		//If the tile is non-null, turn it null
		if (Grid[Index] != NULL_VECTOR)
		{
			//Nullify the tile
			Grid[Index] = NULL_VECTOR;

			//Remove unneessary tiles from the end
			if (Grid.Num() > 0)
			{
				int k = Grid.Num() - 1;
				while (Grid.IsValidIndex(k) && Grid[k] == NULL_VECTOR)
				{
					Grid.RemoveAt(k);
					k = k - 1;
				}
			}

			//Update the grid sizes
			UpdateAllSizes();
		}

		//If the tile is null, do nothing
	}

	//If outside the bounds of the grid, do nothing

	//Check the grid itself
	UE_LOG(LogTemp, Warning, TEXT("After updating, the grid looks like: "));
	for (int i = 0; i < Grid.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grid[%d] = (%f, %f, %f)"), i, Grid[i].X, Grid[i].Y, Grid[i].Z);
	}*/
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

void ASquareGrid::UpdateSizeX()
{

	/*UE_LOG(LogTemp, Warning, TEXT("Old Size X is %d"), SizeX);

	//Find how many cells are in the X dimension. Done by checking all in first X row
	float LargestCoordInX = GetGridOrigin().X;

	//Iterate through all of the locations, checking for the largest X
	for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i].X > LargestCoordInX && Grid[i] != NULL_VECTOR)
		{
			LargestCoordInX = Grid[i].X;
		}
	}

	float LengthX = LargestCoordInX - GetGridOrigin().X;

	//Update accordingly. Also it's probably a good idea to check for rounding errors here, which is why we're using round
	if (Grid.Num() == 0)
	{
		SizeX = 0;
	}
	else
	{
		SizeX = round(LengthX / GetTileLength()) + 1;
	}

	UE_LOG(LogTemp, Warning, TEXT("New Size X is %d"), SizeX);*/

}

void ASquareGrid::UpdateSizeY()
{
	/*UE_LOG(LogTemp, Warning, TEXT("Old Size Y is %d"), SizeY);

	//Find how many cells are in the X dimension. Done by checking all in first X row
	float LargestCoordInY = GetGridOrigin().Y;

	//Iterate through all of the locations, checking for the largest X
	for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i].Y > LargestCoordInY && Grid[i] != NULL_VECTOR)
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
	if (Grid.Num() == 0)
	{
		SizeY = 0;
	}
	else
	{
		SizeY = round(WidthY / GetTileWidth()) + 1;
	}

	UE_LOG(LogTemp, Warning, TEXT("New Size Y is %d"), SizeY);*/
}

void ASquareGrid::UpdateSizeZ()
{

	/*UE_LOG(LogTemp, Warning, TEXT("Old Size Z is %d"), SizeZ);

	//Find how many cells are in the X dimension. Done by checking all in first X row
	float LargestCoordInZ = GetGridOrigin().Z;

	//Iterate through all of the locations, checking for the largest X
	for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i].Z > LargestCoordInZ && Grid[i] != NULL_VECTOR)
		{
			LargestCoordInZ = Grid[i].Z;
		}
	}

	float HeightZ = LargestCoordInZ - GetGridOrigin().Z;

	//Update accordingly. Also it's probably a good idea to check for rounding errors here, which is why we're using round
	if (Grid.Num() == 0)
	{
		SizeZ = 0;
	}
	else
	{
		SizeZ = round(HeightZ / GetTileHeight()) + 1;
	}

	UE_LOG(LogTemp, Warning, TEXT("New Size Z is %d"), SizeZ);*/

}

void ASquareGrid::UpdateAllSizes()
{
	/*UpdateSizeX();
	UpdateSizeY();
	UpdateSizeZ();*/
}

int ASquareGrid::GetNumSpaces() const
{
	//Count the number of non-NULL_VECTOR elements in the array
	int count = 0;

	for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i] == NULL_VECTOR)
		{
			count++;
		}
	}

	return count;
}