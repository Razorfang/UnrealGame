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
		//GridMesh->SetStaticMesh(CellAsset.Object);

		/*Set the mesh location so that it is located at the only cell
		TODO: Check if we want the point to be the middle or the bottom-left corner
		This is just a test*/

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Square grid initialized. TW,TL,TH,SX,SY,SZ,origin: %f,%f,%f,%d,%d,%d,(%f %f %f)"), TileWidth, TileLength, TileHeight, SizeX, SizeY, SizeZ, GetGridOrigin().X, GetGridOrigin().Y, GetGridOrigin().Z));

		//To set sizes appropriately, we need bounding boxes

	}
}

void ASquareGrid::PrintDebug()
{
	UE_LOG(LogTemp, Warning, TEXT("After updating, the grid looks like: "));
	for (int i = 0; i < Grid.Num(); i++)
	{
		if (!IsValid(Grid[i]))
		{
			UE_LOG(LogTemp, Warning, TEXT("nullptr at index %d"), i);
		}
		else
		{
			FVector WorldLocation = Grid[i]->GetWorldLocation();
			UE_LOG(LogTemp, Warning, TEXT("Grid[%d] = (%f, %f, %f)"), i, WorldLocation.X, WorldLocation.Y, WorldLocation.Z);
		}
	}
}

ASquareGridTile* ASquareGrid::SpawnSquareGridTile(int x, int y, int z, float pitch, float yaw, float roll, UStaticMeshComponent* mesh, bool state)
{
	FVector TileLocation = CoordToWorld(x, y, z);
	FRotator TileRotation(pitch, yaw, roll); //TODO: Rotating the grid should also rotate the tiles
	FActorSpawnParameters SpawnInfo;

	//Create a new tile
	ASquareGridTile* SquareTile = GetWorld()->SpawnActor<ASquareGridTile>(TileLocation, TileRotation, SpawnInfo);
	if (!IsValid(SquareTile))
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to spawn tile at %d,%d,%d"), x, y, z);
	}
	else
	{

		//Set the tile's location
		SquareTile->SetWorldLocation(CoordToWorld(x, y, z));

		//Set the tile's mesh
		SquareTile->SetTileMesh(mesh);

		//Set the tile's state
		SquareTile->SetIsHighlighted(state);

		//Set the tile's length, width, and height
		SquareTile->SetTileLength(TileLength);
		SquareTile->SetTileWidth(TileWidth);
		SquareTile->SetTileHeight(TileHeight);
	}

	return SquareTile;
}


FVector ASquareGrid::CoordToWorld(int x, int y, int z) const
{
	FVector GridOrigin = GetGridOrigin();
	FVector NewTile(GridOrigin.X + GetTileLength() * x, GridOrigin.Y + GetTileWidth() * y, GridOrigin.Z + GetTileHeight() * z);

	return NewTile;
}

void ASquareGrid::InitTiles(int length, int width, int height, bool AllTilesState, UStaticMeshComponent* AllTilesMesh)
{


	if (length == 0 && width == 0 && height == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("You are trying to initialize an empty grid with nothing. Why would you do this?"));
	}
	else if (Grid.Num() != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please don't call this function if the grid is non-empty"));
	}
	else
	{

		//Iterate over each tile, initializing each one, and setting up the grid properly
		SizeX = length;
		SizeY = width;
		SizeZ = height;

		//TODO: Set the Tile Length, width, and height parameter

		for (int z = 0; z < SizeZ; z++)
		{
			for (int y = 0; y < SizeY; y++)
			{
				for (int x = 0; x < SizeX; x++)
				{

					ASquareGridTile* SquareTile = SpawnSquareGridTile(x, y, z, 0, 0, 0, AllTilesMesh, AllTilesState);

					//Add the tile to the grid. Due to our loop structure going through x, then y, then z, the places will be correct
					if (IsValid(SquareTile))
					{
						Grid.Add(SquareTile);
					}
				}
			}
		}

		//TODO: Scale the plane mesh so that it is the right size
		//FVector NewScale(length, width, 1);
		//GridMesh->SetWorldScale3D(NewScale);


	}

	//Check the grid itself
	UE_LOG(LogTemp, Warning, TEXT("After updating, the grid looks like: "));
	for (int i = 0; i < Grid.Num(); i++)
	{
		FVector Location = Grid[i]->GetWorldLocation();
		UE_LOG(LogTemp, Warning, TEXT("Grid[%d] is located at (%f, %f, %f)"), Location.X, Location.Y, Location.Z);
	}
}


void ASquareGrid::SetTilesMesh(UStaticMeshComponent* AllTilesMesh)
{
	for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i] != nullptr)
		{
			Grid[i]->SetTileMesh(AllTilesMesh);
		}
	}
}


void ASquareGrid::SetTilesHighlighted(bool AllTilesHighlightedState)
{
	for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i] != nullptr)
		{
			Grid[i]->SetIsHighlighted(AllTilesHighlightedState);
		}
	}
}


unsigned int ASquareGrid::CoordToIndex(int x, int y, int z) const
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

	return (SizeX * SizeY) * z + (SizeX)* y + x;

}


bool ASquareGrid::IsWithinBounds(int x, int y, int z) const
{
	if (x >= SizeX || y >= SizeY || z >= SizeZ)
	{
		return false;
	}

	return true;
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

/*void ASquareGrid::InitTiles(int length, int width, int height, bool AllTilesState, UStaticMeshComponent* AllTilesMesh)
{

}*/


FVector ASquareGrid::GetTileCoord(ASquareGridTile* Tile) const
{
	//Get grid origin
	FVector GridOrigin = GetGridOrigin();

	//Get tile origin
	FVector TileOrigin = Tile->GetWorldLocation();

	//Use difference to calculate

	int x = roundf((TileOrigin.X - GridOrigin.X) / TileLength);
	int y = roundf((TileOrigin.Y - GridOrigin.Y) / TileWidth);
	int z = roundf((TileOrigin.Z - GridOrigin.Z) / TileHeight);

	return FVector(x, y, z);
}


void ASquareGrid::AddTile(int x, int y, int z, UStaticMeshComponent* NewTileMesh, bool NewTileIsHighlighted)
{
	//FVector NewTile = CoordToWorld(x, y, z);
	UE_LOG(LogTemp, Warning, TEXT("New Tile Location: %f, %f, %f"), x, y, z);

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
			//Add a null tile
			Grid.Add(nullptr);
		}
		//spawn a tile
		ASquareGridTile* NewTile = SpawnSquareGridTile(x, y, z, 0, 0, 0, NewTileMesh, NewTileIsHighlighted);

		//add the tile to the grid
		Grid.Add(NewTile);
	}

	//If adding a tile within bounds
	else if (IsWithinBounds(x, y, z))
	{
		UE_LOG(LogTemp, Warning, TEXT("Tile we want to add is within bounds"));

		//We can calculate the index better if we're in bounds
		int index = CoordToIndex(x, y, z);

		//If it's null, replace it
		if (Grid[index] == nullptr)
		{
			//spawn a tile
			ASquareGridTile* NewTile = SpawnSquareGridTile(x, y, z, 0, 0, 0, NewTileMesh, NewTileIsHighlighted);

			//add the tile to the grid
			Grid[index] = NewTile;

			UE_LOG(LogTemp, Warning, TEXT("Nothing here"));
		}

		//Otherwise, do nothing, since a tile is already there
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Something here"));
		}
	}

	//If it's outside of bounds, then we need to resize the grid accordingly. This is the tricky part
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tile we want to add is out of bounds"));

		//Readjust the grid sizes based on the largest of two values
		if (x >= SizeX) { SizeX = x + 1; UE_LOG(LogTemp, Warning, TEXT("New SizeX is %d"), SizeX); }
		if (y >= SizeY) { SizeY = y + 1; UE_LOG(LogTemp, Warning, TEXT("New SizeY is %d"), SizeY); }
		if (z >= SizeZ) { SizeZ = z + 1; UE_LOG(LogTemp, Warning, TEXT("New SizeZ is %d"), SizeZ); }

		//Resize the grid appropriately, by adding more nulls
		for (int j = Grid.Num(); j < (SizeX * SizeY * SizeZ); j++)
		{
			Grid.Add(nullptr);
		}

		//Move all tiles to new spots:

		//Get the new index - this works since we resized the grid, so this is now within boundaries
		int NewIndex = CoordToIndex(x, y, z);
		UE_LOG(LogTemp, Warning, TEXT("New index is %d"), NewIndex);

		//Move all the existing tiles to their correct places
		//BIG TODO

		//For each tile
			//Get the (x,y,z)
			//Convert to new index
			//Move tile to that index

		//Move everything at and after index to the end
		int k = Grid.Num() - 1;
		//while (k > NewIndex)
		while (k >= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Checking"));
			//Tile
			if (IsValid(Grid[k]))
			{
				UE_LOG(LogTemp, Warning, TEXT("Valid"));

				//Get the (x,y,z)
				FVector coords = GetTileCoord(static_cast<ASquareGridTile* >(Grid[k]));
				UE_LOG(LogTemp, Warning, TEXT("Coords"));

				//Convert to new index
				int NewIndex = CoordToIndex(coords.X, coords.Y, coords.Z);
				UE_LOG(LogTemp, Warning, TEXT("New"));

				//Move tile to that index
				Grid.Swap(k, NewIndex);
				UE_LOG(LogTemp, Warning, TEXT("Swap"));

				//Grid.Swap(k, k - 1);
			}

			k--;

		}
		UE_LOG(LogTemp, Warning, TEXT("Swapping done"));

		//Put new tile in its place - at the end
		ASquareGridTile* NewTile = SpawnSquareGridTile(x, y, z, 0, 0, 0, NewTileMesh, NewTileIsHighlighted);
		Grid[NewIndex] = NewTile;
		UE_LOG(LogTemp, Warning, TEXT("Assigning done"));
	}

	//Check the grid itself
	PrintDebug();
}


void ASquareGrid::NullifyTile(int x, int y, int z)
{
	//Nullifying certain tiles will cause the grid to be resized

	FVector NewTile = CoordToWorld(x, y, z);
	UE_LOG(LogTemp, Warning, TEXT("Nulled Tile Location: %f, %f, %f"), NewTile.X, NewTile.Y, NewTile.Z);

	//If the tile is within bounds
	if (IsWithinBounds(x, y, z))
	{
		//We can calculate the index better if we're in bounds
		int index = CoordToIndex(x, y, z);

		//Nullify that tile, meaning we make it invisible
		HideGridTile(Grid[index]);

		//TODO: If we need to resize the grid, do so. This involves removing trailing nulls, and changing the size fields
	}

	//Otherwise, the tile is out of bounds, and we don't do anything
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tile we want to nullify is out of bounds. Nothing to do"));
	}

	//Check the grid itself
	PrintDebug();
}


bool ASquareGrid::TileIsValid(int x, int y, int z)
{
	unsigned int index = CoordToIndex(x, y, z);
	return IsValid(Grid[index]);
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
	/*for (int i = 0; i < Grid.Num(); i++)
	{
		Grid[i].Y = NewWidth;
	}*/

	/* TODO: Correct the appearance of the grid mesh */
}

void ASquareGrid::SetTileLength(float NewLength)
{
	check((NewLength > 0) && "Do not set the tile length to that! Delete the grid instead");
	TileLength = NewLength;

	/* Change the X-value of all points in the grid */
	/*for (int i = 0; i < Grid.Num(); i++)
	{
		Grid[i].X = NewLength;
	}*/

	/* TODO: Correct the appearance of the grid mesh */
}

void ASquareGrid::SetTileHeight(float NewHeight)
{
	TileHeight = NewHeight;

	/* Change the Z-value of all points in the grid */
	/*for (int i = 0; i < Grid.Num(); i++)
	{
		Grid[i].Z = NewHeight;
	}*/

	/* TODO: Correct the appearance of the grid mesh */
}

void ASquareGrid::UpdateSizeX()
{

	UE_LOG(LogTemp, Warning, TEXT("Old Size X is %d"), SizeX);

	//Find how many cells are in the X dimension. Done by checking all in first X row
	float LargestCoordInX = GetGridOrigin().X;

	//Iterate through all of the locations, checking for the largest X
	/*for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i].X > LargestCoordInX && Grid[i] != NULL_VECTOR)
		{
			LargestCoordInX = Grid[i].X;
		}
	}*/

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

	UE_LOG(LogTemp, Warning, TEXT("New Size X is %d"), SizeX);

}

void ASquareGrid::UpdateSizeY()
{
	UE_LOG(LogTemp, Warning, TEXT("Old Size Y is %d"), SizeY);

	//Find how many cells are in the X dimension. Done by checking all in first X row
	float LargestCoordInY = GetGridOrigin().Y;

	//Iterate through all of the locations, checking for the largest X
	/*for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i].Y > LargestCoordInY && Grid[i] != NULL_VECTOR)
		{
			UE_LOG(LogTemp, Warning, TEXT("Grid[i] = %f"), Grid[i].Y);
			LargestCoordInY = Grid[i].Y;
		}
	}*/

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

	UE_LOG(LogTemp, Warning, TEXT("New Size Y is %d"), SizeY);
}

void ASquareGrid::UpdateSizeZ()
{

	UE_LOG(LogTemp, Warning, TEXT("Old Size Z is %d"), SizeZ);

	//Find how many cells are in the X dimension. Done by checking all in first X row
	float LargestCoordInZ = GetGridOrigin().Z;

	//Iterate through all of the locations, checking for the largest X
	for (int i = 0; i < Grid.Num(); i++)
	/*{
		if (Grid[i].Z > LargestCoordInZ && Grid[i] != NULL_VECTOR)
		{
			LargestCoordInZ = Grid[i].Z;
		}
	}*/

	float HeightZ = LargestCoordInZ - GetGridOrigin().Z;

	//Update accordingly. Also it's probably a good idea to check for rounding errors here, which is why we're using round
	if (Grid.Num() == 0)
	{
		SizeZ = 0;
	}
	else
	{
		//SizeZ = round(HeightZ / GetTileHeight()) + 1;
	}

	UE_LOG(LogTemp, Warning, TEXT("New Size Z is %d"), SizeZ);

}

void ASquareGrid::UpdateAllSizes()
{
	UpdateSizeX();
	UpdateSizeY();
	UpdateSizeZ();
}

int ASquareGrid::GetNumSpaces() const
{
	//Count the number of non-NULL_VECTOR elements in the array
	int count = 0;

	for (int i = 0; i < Grid.Num(); i++)
	{
		if (Grid[i] != nullptr)
		{
			count++;
		}
	}

	return count;
}