// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "SquareGridTile.h"
#include "SquareGrid.generated.h"


/**
*
*/
UCLASS()
class TACTICSGAME_API ASquareGrid : public AGrid
{
	GENERATED_BODY()

public:

	ASquareGrid();

	/* Initialize a grid full of tiles, with dimensions X, Y, Z.
	AllTilesState will denote whether all tiles are valid (true) or all tiles are invalid (false)*/
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void InitTiles(int length, int width, int height, bool AllTilesState, UStaticMeshComponent* AllTilesMesh); ///

	/* Initialize a grid full of tiles, using an array of something*/
	//I found out that apparently, you cannot overload UFUNCTIONs
	/*UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void InitTiles(int length, int width, int height);*/

	/* Give all tiles in the grid the passed mesh */
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetTilesMesh(UStaticMeshComponent* AllTilesMesh); ///

	/* Make every tile in the grid highlighted (true) or not (false) */
	/* Give all tiles in the grid the passed mesh */
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetTilesHighlighted(bool AllTilesHighlightedState); ///

	/* Add a tile to the grid at a specified point in space */
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void AddTile(int x, int y, int z, UStaticMeshComponent* NewTileMesh, bool NewTileIsHighlighted);

	/* Remove a tile entirely (despawn it). This is different to nullifying, which just makes it invisible to the game */
	//UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	//void RemoveTile(int x, int y, int z);

	/*Hide the tile. It still exists in memory, but it will not be visible to the game*/
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void NullifyTile(int x, int y, int z); 

	/*Undo the effects of NullifyTile */
	//UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	//void DeNullifyTile(int x, int y, int z);

	/*Check if the grid location is a valid tile*/
	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	bool TileIsValid(int x, int y, int z); ///


	/* Width is Y, Length is X, Height is Z */
	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	float GetTileWidth() const; ///
	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	float GetTileLength() const; ///
	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	float GetTileHeight() const; ///
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetTileWidth(float NewWidth); ///
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetTileLength(float NewLength); ///
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetTileHeight(float NewHeight); ///

	//TODO: Put these back
	/*UFUNCTION(BlueprintPure, Category = "SquareGrid")
		int GetSizeX() const;
	UFUNCTION(BlueprintPure, Category = "SquareGrid")
		int GetSizeY() const;
	UFUNCTION(BlueprintPure, Category = "SquareGrid")
		int GetSizeZ() const;
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
		void SetSizeX(int NewSizeX);
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
		void SetSizeY(int NewSizeY);
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
		void SetSizeZ(int NewSizeZ);*/

	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	int GetNumSpaces() const; ///

	 /* Calculates the world position of the tile at coordinate (x,y,z) */
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	FVector CoordToWorld(int x, int y, int z) const; ///

	/* Get the cartesian (x,y,z) of a tile */
	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	FVector GetTileCoord (ASquareGridTile* Tile) const;

	/* TODO: Add a row of tiles */

	/* TODO: Add a column of tiles */

	/* TODO: Add a pillar of tiles */

private:
	/* Used to determine how wide this grid is. This is what we multiply by to translate cartesian to world. Used to scale Y */
	float TileWidth;

	/* Used to determine how long the grid is This is what we multiply by to translate cartesian to world. Used to scale X */
	float TileLength;

	/* Used to determine how tall the grid is, for 3D grids. Used to scale Z */
	float TileHeight;

	/* Records the number of tiles in each direction*/
	int SizeX;
	int SizeY;
	int SizeZ;


	/* Converts an (x,y,z) point into an index for the Grid array
	This should only be used for getting the index of tiles WITHIN BOUNDS*/
	unsigned int CoordToIndex(int x, int y, int z) const;

	/* Checks if (x,y,z) is within the bounds of the grid. Return true if it is and false if it isn't */
	bool IsWithinBounds(int x, int y, int z) const; 

	/* To be called after a tile as added or removed from the grid, so that we have it correct*/
	void UpdateSizeX(); 
	void UpdateSizeY(); 
	void UpdateSizeZ();
	void UpdateAllSizes(); 

	void RecursiveSwap(int i);

	//Spawns a SquareGridTile. Will return an invalid tile if spawning was unsuccessful
	ASquareGridTile* SpawnSquareGridTile(int x, int y, int z, float pitch, float yaw, float roll, UStaticMeshComponent* mesh, bool state); ///

	void PrintDebug();

};
