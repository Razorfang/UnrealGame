// Fill out your copyright notice in the Description page of Project Settings.

#include "SquareGrid.h"

// Sets default values
ASquareGrid::ASquareGrid()
{
	/*Set this grid's type, changing it from UNKNOWN to SQUARE*/
	GridType = EGridType::ESquare;

	//Set up the grid default size, a 1x1 grid
	GridWidth = 1;
	GridLength = 1;
	GridHeight = 0;

	/*Resize the grid appropriately*/
	Grid.Init(NULL_VECTOR, 1);
}

int ASquareGrid::GetGridWidth() const
{
	return GridWidth;
}

int ASquareGrid::GetGridLength() const
{
	return GridLength;
}

int ASquareGrid::GetGridHeight() const
{
	return GridHeight;
}

void ASquareGrid::SetGridWidth(int NewWidth)
{
	check((NewWidth > 0) && "Do not set the width to that! Delete the grid instead");
	GridWidth = NewWidth;

	//TODO: Resize the grid
}

void ASquareGrid::SetGridLength(int NewLength)
{
	check((NewLength > 0) && "Do not set the length to that! Delete the grid instead");
	GridLength = NewLength;

	//TODO: Resize the grid

}

void ASquareGrid::SetGridHeight(int NewHeight)
{
	GridHeight = NewHeight;

	//TODO: Resize the grid
}

void ASquareGrid::AddTile(int x, int y, int z)
{
	/* TODO */
}

void ASquareGrid::RemoveTile(int x, int y, int z)
{
	/* TODO */
}