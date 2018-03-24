// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

/*
* Enumeration to keep track of the type of grid. This drastically affects the source code, so it's important to keep track
*/
UENUM(BlueprintType)
enum class EGridType : uint8
{
	EUnknown,
	ETriangle,
	ESquare,
	EHexagon
};

UCLASS()
class TACTICS_API AGrid : public AActor
{
	GENERATED_BODY()

public:
	/* Initialize a grid
	* The default constructor can get away with doing nothing because we always call a specific type anyway*/
	AGrid();

	/* Called every frame */
	virtual void Tick(float DeltaTime) override;

	/* Get the type of grid this is. There is no setter because a grid MUST keep its type consistant */
	UFUNCTION(BlueprintPure, Category="Grid")
	EGridType GetGridType();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* This grid's type */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grid")
	EGridType GridType;

	/*
	Array of vectors, used to store the structure of the grid
	The reason we store an array of vectors at each point is to allow for multilevel maps (e.g. going underneath a bridge)
	When the mouse moves over a space, hitting a key should switch between different vertical layers if possible.
	Actually, since nested TArrays are not supported, we'll just use arithmetic to treat a 1D array as a 2D array, based on x and y
	This also is the most flexible way to hold it.
	This type of grid means we can easily shift between any number of dimensions, depending on our game type
	*/
	TArray<FVector> Grid;

	/* Static mesh to represent the grid in the level 
	This works by defining a mesh for a space of the grid (such as a square or hex), and copying it for each space*/ 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* GridMesh;

};
