// Fill out your copyright notice in the Description page of Project Settings.


#include "PressForwardSlalom.h"


// Sets default values
APressForwardSlalom::APressForwardSlalom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APressForwardSlalom::BeginPlay()
{
	Super::BeginPlay();
	
}

FIntVector APressForwardSlalom::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
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

	//DirectPath
	pos=(FVector)(StartPos+FIntVector(-Offset+1,2,-1));
	FVector Endpos=(FVector)(StartPos+FIntVector(SizeX-Offset-2,2,-1));
	Size =FVector(1,SizeY-4,1);
	GridActor->BuildMovingPlatform(pos,pos+(Endpos-pos)/2-FVector(0.5,0,0),((SizeX-2))*(0.75),Size,EMaterialSplat::Visible);
	GridActor->BuildMovingPlatform(pos+(Endpos-pos)/2+FVector(0.5,0,0),Endpos,((SizeX-2))*(0.75),Size,EMaterialSplat::Visible,0,false);
	
	for (int y = 2; y < SizeY-3; ++y)
	{
		// TODO: Random Skip 
		int x = FMath::RandRange(0,SizeX-3);
		y+=1;//skip row

		FVector pos2=(FVector)(StartPos+FIntVector(1-Offset,y,0));
		FVector Size2 =FVector(x,1,1);
		if(Size2.X>0.1f)
			GridActor->BuildPlatform(pos2,Size2,EMaterialSplat::Invisible);
		pos2+=FVector(x+1,0,0);
		Size2= FVector(SizeX-x-3,1,1);
		if(Size2.X>0.1f)
			GridActor->BuildPlatform(pos2,Size2,EMaterialSplat::Invisible);
		
	}
	/*GridActor->SpawnAmmoInSpawnBlockInGrid(FVector(StartPos)-FVector(Offset-1.f,-1.f,0),
										   FVector(SizeX-2.f,SizeY-2.f,1),100);*/
	return ExitVector;
}


