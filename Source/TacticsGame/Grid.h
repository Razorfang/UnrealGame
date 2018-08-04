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

	AGrid();

	/* Called every frame */
	virtual void Tick(float DeltaTime) override;

	/* Get the type of grid this is. There is no setter because a grid MUST keep its type consistent */
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

	/* This scene component allows the grid to be translated, rotated, and scaled */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	USceneComponent* Root;

	//TODO: Function to spawn a tile

	/* Make a tile invisible, but don't delete it A*/
	void HideGridTile(AGridTile* Tile); ///

	/* Make a tile visible */
	void ShowGridTile(AGridTile* Tile); ///

	/* Remove a tile from existence */
	void DespawnGridTile(AGridTile* Tile);

};
