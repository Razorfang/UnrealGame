// Fill out your copyright notice in the Description page of Project Settings.

#include "SquareGrid.h"

// Sets default values
ASquareGrid::ASquareGrid()
{

	GridType = EGridType::ESquare;

	GridWidth = 1;
	GridLength = 1;
	GridHeight = 0;

	//TODO: Set up the grid default size
}

int ASquareGrid::GetGridWidth()
{
	return GridWidth;
}

int ASquareGrid::GetGridLength()
{
	return GridLength;
}

int ASquareGrid::GetGridHeight()
{
	return GridHeight;
}

void ASquareGrid::SetGridWidth(int NewWidth)
{
	GridWidth = NewWidth;

	//TODO: Resize the grid
}

void ASquareGrid::SetGridLength(int NewLength)
{
	GridLength = NewLength;

	//TODO: Resize the grid
}

void ASquareGrid::SetGridHeight(int NewHeight)
{
	GridHeight = NewHeight;

	//TODO: Resize the grid
}