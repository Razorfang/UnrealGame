// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridTile.h"
#include "GameFramework/Actor.h"
#include "SquareGridTile.generated.h"

UCLASS()
class TACTICSGAME_API ASquareGridTile : public AGridTile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASquareGridTile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Getters
	float GetTileLength() const;
	float GetTileWidth() const;
	float GetTileHeight() const;

	//Setters
	void SetTileLength(float Length);
	void SetTileWidth(float Width);
	void SetTileHeight(float Height);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	/* The length (size in X) of the tile
	This is set by the grid upon object construction, but can be overwritten later if desired */
	float TileLength;

	/* The width (size in X) of the tile */
	float TileWidth;

	/* The height (size in X) of the tile */
	float TileHeight;
	
	
};
