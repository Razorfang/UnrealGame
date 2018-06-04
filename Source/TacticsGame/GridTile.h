// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTile.generated.h"

UCLASS()
class TACTICSGAME_API AGridTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* This vector contains the world location of the middle of the tile */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	FVector WorldLocation;

	/* This mesh represents appearance of the tile in-game */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	class UStaticMeshComponent* TileMesh;

	/* This variable is used to keep track of if the tile is 'highlighted' or not.
	We can use this for, say, noting if the mouse cursor is hovering. We can then
	use this to change the texture of the tile if we want */
	bool isHighlighted;
	
};
