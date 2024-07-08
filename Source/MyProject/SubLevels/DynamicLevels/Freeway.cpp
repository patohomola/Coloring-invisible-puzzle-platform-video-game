// Fill out your copyright notice in the Description page of Project Settings.


#include "Freeway.h"


// Sets default values
AFreeway::AFreeway()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFreeway::BeginPlay()
{
	Super::BeginPlay();
	
}

FIntVector AFreeway::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int32 Offset=0;
	FIntVector ExitVector;
	TownSquare(StartPos, SizeX, SizeY, SizeZ, Offset,0, ExitVector, EHouseTheme::Blank);

	//startPlatform
	FVector pos=(FVector)(StartPos+FIntVector(-Offset,0,-1));
	FVector Size =FVector(SizeX,2,1);
	GridActor->BuildPlatform(pos,Size,EMaterialSplat::Visible);

	//EndPlatform
	pos=(FVector)(StartPos+FIntVector(-Offset,SizeY-2,-1));
	GridActor->BuildPlatform(pos,Size,EMaterialSplat::Visible);

	for (int i = 1; i < SizeY-4; i+=2)
	{
		Size =FVector(SizeX,1,1);
		pos=(FVector)StartPos+FVector(-Offset,2,-1);
		FVector Endpos=(FVector)StartPos+FVector(-Offset,SizeY-2,-1);
		float speed=2;
		float alpha = (float)i / (float)(SizeY-4);
		AMovingPlatform* newPlatform = GridActor->BuildMovingPlatform(pos,Endpos,(SizeY-2)*speed,Size,EMaterialSplat::Visible,alpha,true);
		newPlatform->SetPlatformMovement(EPlatformMovement::ForthTeleport);
	}
	for (int y = 2; y < SizeY-2; ++y)
	{
		for (int x = 0; x < SizeX-1; ++x)
		{
			if(FMath::FRandRange(0.f,1.f)<0.25f)
			{
				pos=(FVector)StartPos+ FVector(x-Offset,y,0);
				Size = FVector(1,1,1);
				GridActor->BuildPlatform(pos,Size,EMaterialSplat::Invisible);
			}
		}
	}

	
	return ExitVector;
}


