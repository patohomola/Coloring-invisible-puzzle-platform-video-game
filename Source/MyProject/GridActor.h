// GridActor.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildBlock.h" // Include the header for the BlockActor class
#include "AGroundFloorBuildBlock.h"
#include "AFloorBuildBlock.h"
#include "ARoofBuildBlock.h"

#include "GridActor.generated.h"


UCLASS()
class MYPROJECT_API AGridActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Number of rows and columns in the grid
	UPROPERTY(EditAnywhere)
	int32 NumRows;

	UPROPERTY(EditAnywhere)
	int32 NumColumns; 

	UPROPERTY(EditAnywhere)
	int32 NumLayers;

	// Spacing between grid elements
	UPROPERTY(EditAnywhere)
	float ElementSpacing;

	UPROPERTY(EditAnywhere)
	float ElementHeightSpacing;
	// Class of the block actor to spawn
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AGroundFloorBuildBlock>> GroundBlockActorClasses;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AFloorBuildBlock>> FloorBlockActorClasses;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ARoofBuildBlock>> RoofBlockActorClasses;	

	// Method to generate the 3D grid and spawn block actors
	UFUNCTION(BlueprintCallable)
	void GenerateGrid();

	UFUNCTION(BlueprintCallable)
	void BuildHouse(int32 X, int32 Y, int32 Z, int32 Height);
	

private:
	// Array to hold references to spawned block actors
	TArray<ABuildBlock*> SpawnedBlocks;
};


