// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GridTile.h"
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
class TACTICSGAME_API AGrid : public AActor
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

	/* Array of tiles, used to store the structure of the grid */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	TArray<AGridTile *> Grid;

	/* Static mesh to represent the grid in the level */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	class UStaticMeshComponent* GridMesh;


};
