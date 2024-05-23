// Fill out your copyright notice in the Description page of Project Settings.


#include "HighWire.h"


// Sets default values
AHighWire::AHighWire()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

// Called when the game starts or when spawned
void AHighWire::BeginPlay()
{
	Super::BeginPlay();
	
}

FIntVector AHighWire::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int32 Ofset;
	FIntVector exitVector;
	TownSquare(StartPos, SizeX, SizeY, SizeZ, Ofset, exitVector, EHouseTheme::Blank);
	FIntVector delta = exitVector-=StartPos;
	exitVector+=FIntVector(0,1,0);
	return exitVector;
}


