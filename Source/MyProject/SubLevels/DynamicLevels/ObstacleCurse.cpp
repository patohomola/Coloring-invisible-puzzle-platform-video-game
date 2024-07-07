// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleCurse.h"


// Sets default values
AObstacleCurse::AObstacleCurse()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AObstacleCurse::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
FIntVector AObstacleCurse::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int32 Offset=0;
	FIntVector exitVector;
	TownSquare(StartPos, SizeX, SizeY, SizeZ, Offset,0, exitVector, EHouseTheme::Blank);

	//startPlatform
	FVector pos=(FVector)(StartPos+FIntVector(-Offset,0,-1));
	FVector Size =FVector(SizeX,2,1);
	GridActor->BuildPlatform(pos,Size,EMaterialSplat::Visible);

	//EndPlatform
	pos=(FVector)(StartPos+FIntVector(-Offset,SizeY-2,-1));
	GridActor->BuildPlatform(pos,Size,EMaterialSplat::Visible);

	//DirectPath
	pos=(FVector)(StartPos+FIntVector(0,2,-1));
	Size =FVector(1,SizeY-4,1.1);
	GridActor->BuildPlatform(pos,Size,EMaterialSplat::Visible);
	
	
	for (int y = 2; y < SizeY-3; ++y)
	{
		// TODO: Random Skip 
		int x = FMath::RandRange(0,SizeX-3);
		y+=1;//skip row

		pos=(FVector)(StartPos+FIntVector(-2-Offset,y,0));
		Size =FVector(0+SizeX,1,1);

		float RandomFloat = FMath::FRand();
		bool bRandomBool = FMath::FRand()<0.5f?true:false;
		
		GridActor->BuildMovingPlatform(pos-FVector(SizeX-3,0.f,0.f),pos,SizeX*(1),Size,EMaterialSplat::Invisible ,RandomFloat,bRandomBool);
		pos+=FVector(1+SizeX,0,0);
		GridActor->BuildMovingPlatform(pos-FVector(SizeX-3,0.f,0.f),pos,SizeX*(1),Size,EMaterialSplat::Invisible,RandomFloat,bRandomBool);

		//press Forward Hack breaker
		
		GridActor->BuildMovingPlatform(pos-FVector(SizeX-3-0.05,0.125f,0.f),pos-FVector(0-0.05,0.125f,0),SizeX*(1),FVector(0.25,1.25,1.1),EMaterialSplat::Invisible ,RandomFloat,bRandomBool);
		GridActor->BuildMovingPlatform(pos-FVector(SizeX-2+0.05,0.125f,0.f),pos-FVector(1+0.05,0.125f,0),SizeX*(1),FVector(-0.25,1.25,1.1),EMaterialSplat::Invisible ,RandomFloat,bRandomBool);
	}
	return exitVector;
}


