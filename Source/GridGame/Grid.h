// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

/*
* Enumeration to keep track of the type of grid. This drastically affects the source code, so it's important to keep track
*/

/* Because of the way our grid system works (where tiles can exist anywhere and everything in between
is filled with nothings), we need a way to define these nothings. We can't use (0,0,0) because that may very
well be the location of a grid. For our purposes, we will have a vector located at Infinity, since
we don't want it to exist in-game */
#define NULL_VECTOR FVector(INFINITY, INFINITY, INFINITY) 

UENUM(BlueprintType)
enum class EGridType : uint8
{
	EUnknown,
	ETriangle,
	ESquare,
	EHexagon
};

UCLASS()
class GRIDGAME_API AGrid : public AActor
{
	GENERATED_BODY()

public:
	/* Initialize a grid
	* The default constructor can get away with doing nothing because we always call a specific type anyway*/
	AGrid();

	/* Called every frame */
	virtual void Tick(float DeltaTime) override;

	/* Get the type of grid this is. There is no setter because a grid MUST keep its type consistant */
	UFUNCTION(BlueprintPure, Category = "Grid")
		EGridType GetGridType() const;

	/* The grid origin is the position of where the first space on the grid would be placed.
	This is just the location of the Root Component, so we don't need to define a class variable*/
	UFUNCTION(BlueprintPure, Category = "Grid")
		FVector GetGridOrigin() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* This grid's type */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
		EGridType GridType;

	/*
	Array of vectors, used to store the structure of the grid
	The reason we store an array of vectors at each point is to allow for multilevel maps (e.g. going underneath a bridge)
	When the mouse moves over a space, hitting a key should switch between different vertical layers if possible.
	Actually, since nested TArrays are not supported, we'll just use arithmetic to treat a 1D array as a 2D array, based on x and y
	This also is the most flexible way to hold it.
	This type of grid means we can easily shift between any number of dimensions, depending on our game type
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
		TArray<FVector> Grid;

	/* Static mesh to represent the grid in the level
	This works by defining a mesh for a space of the grid (such as a square or hex), and copying it for each space*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
		class UStaticMeshComponent* GridMesh;

};