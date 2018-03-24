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
	int GetGridWidth();

	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	int GetGridLength();

	UFUNCTION(BlueprintPure, Category = "SquareGrid")
	int GetGridHeight();

	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetGridWidth(int NewWidth);

	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetGridLength(int NewLength);

	UFUNCTION(BlueprintCallable, Category = "SquareGrid")
	void SetGridHeight(int NewHeight);



private:
	/* Used to determine how wide this grid is */
	int GridWidth;

	/* Used to determine how long the grid is */
	int GridLength;

	/* Used to determine how tall the grid is, for 3D grids */
	int GridHeight;
	
};
