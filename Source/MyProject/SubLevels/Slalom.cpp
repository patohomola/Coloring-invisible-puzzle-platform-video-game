// Fill out your copyright notice in the Description page of Project Settings.


#include "Slalom.h"


// Sets default values
ASlalom::ASlalom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

FIntVector ASlalom::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int Offset=0;
	FIntVector ExitVector;
	ARoom::Structure(StartPos,SizeX,SizeY,SizeZ,Offset,0,ExitVector,EHouseTheme::Normal);

	for (int y = 2; y < SizeY-3; ++y)
	{
		// TODO: Random Skip 
		int x = FMath::RandRange(0,SizeX-3);
		y+=1;//skip row

		FVector pos=(FVector)(StartPos+FIntVector(1-Offset,y,0));
		FVector Size =FVector(x,1,1);
		if(Size.X>0.1f)
			GridActor->BuildPlatform(pos,Size,EMaterialSplat::Visible);
		pos+=FVector(x+1,0,0);
		Size= FVector(SizeX-x-3,1,1);
		if(Size.X>0.1f)
			GridActor->BuildPlatform(pos,Size,EMaterialSplat::Visible);
		
	}
	GridActor->SpawnAmmoInSpawnBlockInGrid(FVector(StartPos)-FVector(Offset-1.f,-1.f,0),
										   FVector(SizeX-2.f,SizeY-2.f,1),100);
	return ExitVector;
}
