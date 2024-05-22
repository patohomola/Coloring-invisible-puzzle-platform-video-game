// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"



// Sets default values
ARoom::ARoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

void ARoom::BeginPlay()
{
	/*FVector MyFVector=GridActor->GetActorLocation();
	FIntVector MyFIntVector;

	// Convert FVector to FIntVector
	MyFIntVector.X = FMath::RoundToInt(MyFVector.X);
	MyFIntVector.Y = FMath::RoundToInt(MyFVector.Y);
	MyFIntVector.Z = FMath::RoundToInt(MyFVector.Z*2);
	//GenerateRoom(MyFIntVector,10,10,10);*/
}


FIntVector ARoom::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	if(SizeX<4||SizeY<4)
		return FIntVector::NoneValue;
	if(!GridActor)
		return FIntVector::NoneValue;
	int32 NumRows = SizeX;
	int32 NumColumns = SizeY;
	int32 NumLayers=SizeZ;
	int Ofset = FMath::RandRange(2,SizeX-2);
	int Exit =FMath::RandRange(2,SizeX-2);
	FIntVector exitVector = StartPos + FIntVector(Exit-Ofset,SizeY-1,0);
	for (int32 Row = 0; Row < NumRows; ++Row)
	{
		FIntVector BuildPos = StartPos + FIntVector(Row-Ofset,0,0);
		FIntVector BuildPos2 = StartPos + FIntVector(Row-Ofset,NumColumns-1,0);
		if(BuildPos!=StartPos)
			GridActor->BuildHouse(BuildPos,FMath::RandRange(3,NumLayers), EHouseTheme::Blank);
		if(BuildPos2!=exitVector)
			GridActor->BuildHouse(BuildPos2,FMath::RandRange(3,NumLayers), EHouseTheme::Blank);
	}
	for (int32 Column = 1; Column < NumColumns-1; ++Column)
	{
		FIntVector BuildPos = StartPos + FIntVector(SizeX-1-Ofset,Column,0);
		FIntVector BuildPos2 = StartPos + FIntVector(-Ofset,Column,0);
		GridActor->BuildHouse(BuildPos,FMath::RandRange(3,NumLayers), EHouseTheme::Blank);
		GridActor->BuildHouse(BuildPos2,FMath::RandRange(3,NumLayers), EHouseTheme::Blank);
	}
	GridActor->SpawnAmmoInSpawnBlockInGrid(FVector(StartPos)-FVector(Ofset+0.5f,0+0.5f,0),
		 FVector(SizeX,SizeY,1),100);
	GridActor->BuildPlatform(FVector(StartPos)-FVector(Ofset+0.5f,0+0.5f,1),
		 FVector(SizeX,SizeY,1),
		EMaterialSplat::Visible);
	return exitVector+FIntVector(0,1,0);
}


