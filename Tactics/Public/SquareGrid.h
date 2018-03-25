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
	int GetGridWidth() const;

	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	int GetGridLength() const;

	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	int GetGridHeight() const;

	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetGridWidth(int NewWidth);

	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetGridLength(int NewLength);

	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetGridHeight(int NewHeight);

	/*Add a tile to the grid at a specified point in space*/
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void AddTile(int x, int y, int z);

	/*Remove a tile from the grid, if it exists*/
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void RemoveTile(int x, int y, int z);



private:
	/* Used to determine how wide this grid is. This is what we multiply by to translate cartesian to world */
	float GridWidth;

	/* Used to determine how long the grid is This is what we multiply by to translate cartesian to world */
	float GridLength;

	/* Used to determine how tall the grid is, for 3D grids */
	float GridHeight;
	
};
