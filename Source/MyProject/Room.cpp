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


void ARoom::BuildHouseBlock(FIntVector StartPos, int32 SizeX,int32 SizeY,int32 SizeZ, EHouseTheme Theme)
{
	for (int32 Row = 0; Row < SizeX; ++Row)
	{
		for (int32 Column = 0; Column < SizeY; ++Column)
		{
			FIntVector BuildPos = StartPos + FIntVector(Row,Column,0);
			GridActor->BuildHouse(BuildPos,FMath::RandRange(3, SizeZ), Theme);
		}
	}
}

void ARoom::BuildHouseBlockWithCondition(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ, EHouseTheme Theme, TFunction<bool(FIntVector)> Condition)
{
	for (int32 Row = 0; Row < SizeX; ++Row)
	{
		for (int32 Column = 0; Column < SizeY; ++Column)
		{
			FIntVector BuildPos = StartPos + FIntVector(Row, Column, 0);
			if (Condition(BuildPos))
			{
				GridActor->BuildHouse(BuildPos, FMath::RandRange(3, SizeZ), Theme);
			}
		}
	}
}



void ARoom::TownSquare(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ, int& Ofset,int Exit, FIntVector& exitVector, EHouseTheme theme)
{
	if (Ofset == 0)
		Ofset = FMath::RandRange(1, SizeX - 2);
	if (Exit == 0)
		Exit = FMath::RandRange(1, SizeX - 2);

	// Build obstacle
	GridActor->BuildObstacle(FVector(StartPos) - FVector(Ofset + 1, 1, 1.5f),
							 FVector(SizeX + 2, SizeY + 2, 1));

	// Determine exit position
	exitVector = StartPos + FIntVector(Exit - Ofset, SizeY - 1, 0);

	// Build bottom row and top row with a condition
	BuildHouseBlockWithCondition(
		StartPos + FIntVector(-Ofset, 0, 0), SizeX, 1, SizeZ, theme,
		[&](FIntVector Pos) { return Pos != StartPos; });

	BuildHouseBlockWithCondition(
		StartPos + FIntVector(-Ofset, SizeY - 1, 0), SizeX, 1, SizeZ, theme,
		[&](FIntVector Pos) { return Pos != exitVector; });

	// Build houses for the sides
	BuildHouseBlock(StartPos + FIntVector(-Ofset, 1, 0), 1, SizeY - 2, SizeZ, theme);
	BuildHouseBlock(StartPos + FIntVector(SizeX - 1 - Ofset, 1, 0), 1, SizeY - 2, SizeZ, theme);


	ASpawnManager* spawner =(GridActor->SpawnManager);
	spawner->PopulateArea(
		GridActor->GridCordToRealCord(FVector(StartPos)-FVector(Ofset-1.f,-1.f,0))
		,GridActor->GridScaleToRealScale(FVector(SizeX-2.f,SizeY-2.f,1)),ESpawnSetting::Default);
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


