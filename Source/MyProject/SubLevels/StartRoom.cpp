// Fill out your copyright notice in the Description page of Project Settings.


#include "StartRoom.h"


// Sets default values
AStartRoom::AStartRoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

FIntVector AStartRoom::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int Ofset=-2;
	FIntVector exitVector;
	if (Structure(StartPos-FIntVector(0,-2,0), SizeX, SizeY, 5, Ofset,0, exitVector, EHouseTheme::Blank)) return FIntVector::NoneValue;
	
	return exitVector;
}


// Called when the game starts or when spawned
void AStartRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStartRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

