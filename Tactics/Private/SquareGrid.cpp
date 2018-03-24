// Fill out your copyright notice in the Description page of Project Settings.

#include "SquareGrid.h"

// Sets default values
ASquareGrid::ASquareGrid()
{
	/*Set this grid's type, changing it from UNKNOWN to SQUARE*/
	GridType = EGridType::ESquare;

	//Set up the grid default size
	GridWidth = 1;
	GridLength = 1;
	GridHeight = 0;


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