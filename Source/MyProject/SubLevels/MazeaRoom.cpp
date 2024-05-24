// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeaRoom.h"
#include "../CustomAlgorithm/wiggleRoad.h"

// Sets default values
AMazeaRoom::AMazeaRoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
FIntVector AMazeaRoom::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int32 Ofset;
	FIntVector exitVector;
	Structure(StartPos, SizeX, SizeY, SizeZ, Ofset, exitVector, EHouseTheme::Blank);

	FIntVector delta = exitVector-StartPos;
	Maze mR =Maze(SizeX-1,SizeY-2,Ofset,Ofset+delta.X);
	TArray<Tile> RoadTiles = mR.callculate();

	
	//UE_LOG(LogTemp, Warning, TEXT("Size of RoadTiles: %d"), RoadTiles.Num());
	
	for (int i = 0; i < RoadTiles.Num(); ++i)
	{
		Tile xy=RoadTiles[i];
		//UE_LOG(LogTemp, Warning, TEXT("Tile %d: X = %d, Y = %d"), i, xy.X, xy.Y);
		
		FIntVector roadTile=StartPos+FIntVector(xy.X-Ofset,xy.Y+1,0);
		GridActor->BuildPlatform(FVector(roadTile),
			FVector(1.f,1.f,1.f)
			,EMaterialSplat::Visible);
	}
	//exitVector+=FIntVector(0,1,0);
	return exitVector;
}


// Called when the game starts or when spawned
void AMazeaRoom::BeginPlay()
{
	Super::BeginPlay();
	
}


