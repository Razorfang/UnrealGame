// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTile.generated.h"

/* Used to denote  if a tile's location in the world should be invalidated */
#define NULL_VECTOR FVector(INFINITY, INFINITY, INFINITY) 

UCLASS()
class TACTICSGAME_API AGridTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridTile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Get the world location of this tile */
	UFUNCTION(BlueprintPure, Category = "GridTile")
	FVector GetWorldLocation() const;

	/* Sets the world location of the tile */
	UFUNCTION(BlueprintCallable, Category = "GridTile")
	void SetWorldLocation(FVector NewLocation);

	/* Get the mesh used to represent the tile */
	UFUNCTION(BlueprintPure, Category = "GridTile")
	UStaticMeshComponent* GetTileMesh() const;

	/* Set the mesth used to represent the tile */
	UFUNCTION(BlueprintCallable, Category = "GridTile")
	void SetTileMesh(UStaticMeshComponent* NewTileMesh);

	/* Get the highlighted state of the tile */
	UFUNCTION(BlueprintPure, Category = "GridTile")
	bool GetIsHighlighted() const;

	/* Set the highlighted state of the tile */
	UFUNCTION(BlueprintCallable, Category = "GridTile")
	void SetIsHighlighted(bool HighlightedState);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/* This vector contains the world location of the middle of the tile */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GridTile", meta = (AllowPrivateAccess = "true"))
	FVector WorldLocation;

	/* This mesh represents appearance of the tile in-game. This is an optional parameter, based on if you want your tile to have an appearance
	This is initialized to nullptr*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GridTile", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TileMesh;

	/* This variable is used to keep track of if the tile is 'highlighted' or not.
	We can use this for, say, noting if the mouse cursor is hovering. We can then
	use this to change the texture of the tile if we want 
	This is initialized to false*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GridTile", meta = (AllowPrivateAccess = "true"))
	bool IsHighlighted;

};
