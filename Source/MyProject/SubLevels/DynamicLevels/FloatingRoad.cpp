// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingRoad.h"


// Sets default values
AFloatingRoad::AFloatingRoad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned

FIntVector AFloatingRoad::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int32 Ofset=0;
	FIntVector exitVector;
	TownSquare(StartPos, SizeX, SizeY, SizeZ, Ofset,0, exitVector, EHouseTheme::Blank);

	//startPlatform
	FVector pos=(FVector)(StartPos+FIntVector(-Ofset,0,-1));
	FVector Size =FVector(SizeX,2,1);
	GridActor->BuildPlatform(pos,Size,EMaterialSplat::Visible);

	//EndPlatform
	pos=(FVector)(StartPos+FIntVector(-Ofset,SizeY-2,-1));
	GridActor->BuildPlatform(pos,Size,EMaterialSplat::Visible);

	for (int y = 2; y < SizeY-2; ++y)
	{
		int x = FMath::RandRange(1,SizeX-2);
		FVector Start = (FVector)(StartPos+FIntVector(-Ofset+1,y,-1));
		FVector End = (FVector)(StartPos+FIntVector(-Ofset+SizeX-2,y,-1));
		FVector Size2 =FVector(1,1,1);
		float speed = FMath::FRand()*3.f +1;
		BuildMovingPlatformAtRandom(Start,End,(SizeX-2)*speed,Size2,EMaterialSplat::Invisible);
		//BuildMovingPlatformAtRandom(Start,End,(SizeX-2)*1.f,Size2,EMaterialSplat::Visible);
	}
	
	exitVector+=FIntVector(0,1,0);
	return exitVector;
}

