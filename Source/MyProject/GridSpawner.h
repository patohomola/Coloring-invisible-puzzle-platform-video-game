// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockInfo.h"
#include "GridSpawner.generated.h"

UCLASS()
class MYPROJECT_API AGridSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Number of blocks in each dimension
	UPROPERTY(EditAnywhere, Category = "Grid Settings")
	int32 GridSizeX;

	UPROPERTY(EditAnywhere, Category = "Grid Settings")
	int32 GridSizeY;

	UPROPERTY(EditAnywhere, Category = "Grid Settings")
	int32 GridSizeZ;
	
	// Spacing between blocks
	UPROPERTY(EditAnywhere, Category = "Grid Settings")
	float BlockSpacing;

	// Block class to spawn
	UPROPERTY(EditAnywhere, Category = "Grid Settings")
	TArray<FBlockInfo> BlockTypes; 

	// Called to spawn the grid of blocks
	UFUNCTION(BlueprintCallable, Category = "Grid Functions")
	void SpawnGrid();

};
