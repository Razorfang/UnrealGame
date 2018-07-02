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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	/* The length (size in X) of the tile */
	float TileLength;

	/* The width (size in X) of the tile */
	float TileWidth;

	/* The height (size in X) of the tile */
	float TileHeight;
	
	
};
