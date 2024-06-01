// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicSlalom.h"


// Sets default values
ADynamicSlalom::ADynamicSlalom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADynamicSlalom::BeginPlay()
{
	Super::BeginPlay();
	
}

FIntVector ADynamicSlalom::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int Offset=0;
	FIntVector ExitVector;
	ARoom::Structure(StartPos,SizeX,SizeY,SizeZ,Offset,0,ExitVector,EHouseTheme::Normal);

	for (int y = 2; y < SizeY-3; ++y)
	{
		// TODO: Random Skip 
		int x = FMath::RandRange(0,SizeX-3);
		y+=1;//skip row

		FVector pos=(FVector)(StartPos+FIntVector(-2-Offset,y,0));
		FVector Size =FVector(0+SizeX,1,1);

		float RandomFloat = FMath::FRand();
		bool bRandomBool = FMath::FRand()<0.5f?true:false;
		
		GridActor->BuildMovingPlatform(pos-FVector(SizeX-3,0.f,0.f),pos,SizeX*(1),Size,EMaterialSplat::Invisible ,RandomFloat,bRandomBool);
		pos+=FVector(1+SizeX,0,0);
		GridActor->BuildMovingPlatform(pos-FVector(SizeX-3,0.f,0.f),pos,SizeX*(1),Size,EMaterialSplat::Invisible,RandomFloat,bRandomBool);
		
	}
	GridActor->SpawnAmmoInSpawnBlockInGrid(FVector(StartPos)-FVector(Offset-1.f,-1.f,0),
										   FVector(SizeX-2.f,SizeY-2.f,1),100);
	return ExitVector;
}

