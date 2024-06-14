// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatformRoom.h"


// Sets default values
AMovingPlatformRoom::AMovingPlatformRoom()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMovingPlatformRoom::BuildMovingPlatformAtRandom(FVector StartPosition, FVector EndPosition, float Duration, FVector scalingFactor, EMaterialSplat type)
{
	float RandomFloat = FMath::FRand();
	bool bRandomBool = FMath::FRand()<0.5f?true:false;
	GridActor->BuildMovingPlatform(StartPosition,EndPosition,Duration,scalingFactor,type,RandomFloat,bRandomBool);
}


FIntVector AMovingPlatformRoom::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int32 Ofset=0;
	FIntVector exitVector;
	TownSquare(StartPos, SizeX, SizeY, SizeZ, Ofset,0, exitVector, EHouseTheme::Normal);

	//startPlatform
	FVector pos=(FVector)(StartPos+FIntVector(-Ofset,0,-1));
	FVector Size =FVector(SizeX,2,1);
	GridActor->BuildPlatform(pos,Size,EMaterialSplat::Visible);

	//EndPlatform
	pos=(FVector)(StartPos+FIntVector(-Ofset,SizeY-2,-1));
	GridActor->BuildPlatform(pos,Size,EMaterialSplat::Visible);

	int x = FMath::RandRange(1,SizeX-2);
	FVector Start = (FVector)(StartPos+FIntVector(-Ofset+x,SizeY-3,-1));
	FVector End = (FVector)(StartPos+FIntVector(-Ofset+x,2,-1));
	FVector Size2 =FVector(1,1,1);
	GridActor->BuildMovingPlatform(Start,End,SizeY*1.f,Size2,EMaterialSplat::Invisible);
	
	exitVector+=FIntVector(0,1,0);
	return exitVector;
}



