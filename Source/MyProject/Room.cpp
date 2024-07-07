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


void ARoom::TownSquare(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ, int& Ofset,int Exit, FIntVector& exitVector, EHouseTheme theme)
{
	
	if(Ofset==0)
		Ofset = FMath::RandRange(1,SizeX-2);
	if(Exit==0)
		Exit =FMath::RandRange(1,SizeX-2);
	
	GridActor->BuildObstacle(FVector(StartPos)-FVector(Ofset+1,1,1.5f),
							 FVector(SizeX+2,SizeY+2,1));
	
	exitVector = StartPos + FIntVector(Exit-Ofset,SizeY-1,0);
	for (int32 Row = 0; Row < SizeX; ++Row)
	{
		FIntVector BuildPos = StartPos + FIntVector(Row-Ofset,0,0);
		FIntVector BuildPos2 = StartPos + FIntVector(Row-Ofset,SizeY-1,0);
		if(BuildPos!=StartPos)
			GridActor->BuildHouse(BuildPos,FMath::RandRange(3,SizeZ), theme);
		if(BuildPos2!=exitVector)
			GridActor->BuildHouse(BuildPos2,FMath::RandRange(3,SizeZ), theme);
	}
	for (int32 Column = 1; Column < SizeY-1; ++Column)
	{
		FIntVector BuildPos = StartPos + FIntVector(SizeX-1-Ofset,Column,0);
		FIntVector BuildPos2 = StartPos + FIntVector(-Ofset,Column,0);
		GridActor->BuildHouse(BuildPos,FMath::RandRange(3,SizeZ), theme);
		GridActor->BuildHouse(BuildPos2,FMath::RandRange(3,SizeZ), theme);
	}

	GridActor->SpawnAmmoInSpawnBlockInGrid(FVector(StartPos)-FVector(Ofset-1.f,-1.f,0),
										   FVector(SizeX-2.f,SizeY-2.f,1),(int)((SizeX*SizeY)*0.2f));
}

bool ARoom::Structure(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ, int& Ofset,int Exit, FIntVector& exitVector, EHouseTheme theme)
{
	if(SizeX<3||SizeY<3)
	{
		return true;
	} 
	if(!GridActor)
	{
		return true;
	}
	
	TownSquare(StartPos, SizeX, SizeY, SizeZ, Ofset, Exit, exitVector, theme);
	GridActor->BuildPlatform(FVector(StartPos)-FVector(Ofset,0,1),
	                         FVector(SizeX,SizeY,1),
	                         EMaterialSplat::Visible);
	exitVector+=FIntVector(0,1,0);
	return false;
}

FIntVector ARoom::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int Ofset=0;
	FIntVector exitVector;
	if (Structure(StartPos, SizeX, SizeY, SizeZ, Ofset,0, exitVector, EHouseTheme::Blank)) return FIntVector::NoneValue;
	return exitVector;
}


