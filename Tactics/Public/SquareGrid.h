// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid.h"
#include "SquareGrid.generated.h"

/**
 * 
 */
UCLASS()
class TACTICS_API ASquareGrid : public AGrid
{
	GENERATED_BODY()

	ASquareGrid();

public:
	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	int GetTileWidth() const;

	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	int GetTileLength() const;

	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	int GetTileHeight() const;

	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetTileWidth(float NewWidth);

	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetTileLength(float NewLength);

	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetTileHeight(float NewHeight);

	/*Add a tile to the grid at a specified point in space*/
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void AddTile(int x, int y, int z);

	/*Remove a tile from the grid, if it exists*/
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void RemoveTile(int x, int y, int z);



private:
	/* Used to determine how wide this grid is. This is what we multiply by to translate cartesian to world. Used to scale Y */
	float TileWidth;

	/* Used to determine how long the grid is This is what we multiply by to translate cartesian to world. Used to scale X */
	float TileLength;

	/* Used to determine how tall the grid is, for 3D grids. Used to scale Z */
	float TileHeight;
	
};
