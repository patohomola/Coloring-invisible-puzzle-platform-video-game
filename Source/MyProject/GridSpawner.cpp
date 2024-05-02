// Fill out your copyright notice in the Description page of Project Settings.


// GridSpawner.cpp

#include "GridSpawner.h"
#include "Engine/World.h"
#include "3DBlockTileComponent.h"
// Sets default values
AGridSpawner::AGridSpawner()
{
	// Set default grid size and spacing
	GridSizeX = 5;
	GridSizeY = 5;
	GridSizeZ = 5;
	BlockSpacing = 100.0f; // Adjust this value based on your needs
}

// Called when the game starts or when spawned
void AGridSpawner::BeginPlay()
{
	Super::BeginPlay();

	// Call SpawnGrid function when the game starts (can also be triggered by an event)
	SpawnGrid();
}

void AGridSpawner::SpawnGrid()
{
	FVector SpawnLocation = GetActorLocation();

	for (int32 Z = 0; Z < GridSizeZ; Z++)
	{
		for (int32 Y = 0; Y < GridSizeY; Y++)
		{
			for (int32 X = 0; X < GridSizeX; X++)
			{
				// Calculate spawn location for each block
				FVector NewLocation = SpawnLocation + FVector(X * BlockSpacing, Y * BlockSpacing, Z * BlockSpacing);

				// Spawn block at the calculated location
				int32 BlockIndex = FMath::RandRange(0, BlockTypes.Num() - 1);
				const FBlockInfo& BlockInfo = BlockTypes[BlockIndex];
				AActor* NewBlock = GetWorld()->SpawnActor<AActor>(BlockInfo.BlockActor, NewLocation, FRotator::ZeroRotator);
				if(FMath::RandRange(0, 1)==0)
				{
					U3DBlockTileComponent* Tile =NewBlock->FindComponentByClass<U3DBlockTileComponent>();
					if(Tile)
					{
						//Tile->MirrorX();
						Tile->Rotate90Degrees();
						//Tile->MirrorY();
					}
				}
			}
		}
	}
}



