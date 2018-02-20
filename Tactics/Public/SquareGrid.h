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
	FORCEINLINE int GetGridWidth() const { return GridWidth; };

	FORCEINLINE int GetGridLength() const { return GridLength; };

private:
	/* Used to determine how wide this grid is */
	int GridWidth;

	/* Used to determine how long the grid is */
	int GridLength;
	
	
};
