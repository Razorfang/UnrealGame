// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
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

	/* Initialize a grid full of tiles, with dimensions X, Y, Z. Most common application.
	Should only be called whenever the grid is first constructed */
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void InitTiles(int length, int width, int height); ///

	/*Add a tile to the grid at a specified point in space*/
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
		void AddTile(int x, int y, int z);

	/*Turn a tile into a null vector*/
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
		void NullifyTile(int x, int y, int z); ///



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

	 /* Constructs the vector that should go at the coordinate (x,y,z) */
	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	FVector CoordToWorld(int x, int y, int z) const; ///

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


	/* Converts an (x,y,z) point into an index for the Grid array */
	int CoordToIndex(int x, int y, int z) const;

	/* Checks if (x,y,z) is within the bounds of the grid. Return true if it is and false if it isn't */
	bool IsWithinBounds(int x, int y, int z) const; ///

	/* To be called after a tile as added or removed from the grid, so that we have it correct*/
	void UpdateSizeX(); ///
	void UpdateSizeY(); ///
	void UpdateSizeZ(); ///
	void UpdateAllSizes(); ///

	void RecursiveSwap(int i);
};
