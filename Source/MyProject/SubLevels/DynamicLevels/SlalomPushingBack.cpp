// Fill out your copyright notice in the Description page of Project Settings.


#include "SlalomPushingBack.h"


// Sets default values
ASlalomPushingBack::ASlalomPushingBack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASlalomPushingBack::BeginPlay()
{
	Super::BeginPlay();
	
}

FIntVector ASlalomPushingBack::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int Offset=0;
	FIntVector ExitVector;
	ARoom::Structure(StartPos,SizeX,SizeY,SizeZ,Offset,0,ExitVector,EHouseTheme::Normal);

	GridActor->SpawnAmmoInSpawnBlockInGrid(FVector(StartPos)-FVector(Offset-1.f,-1.f,0),
										   FVector(SizeX-2.f,SizeY-2.f,1),(int)((SizeX*SizeY)*0.4f));

	for (int y = 2; y < SizeY-3; ++y)
	{
		// TODO: Random Skip 
		int x = FMath::RandRange(0,SizeX-3);
		y+=1;//skip row

		FVector EndPos=(FVector)(StartPos+FIntVector(1-Offset,2,0));
		FVector BeginPos=EndPos+(FVector)FIntVector(0,SizeY-5,0);
		FVector Size =FVector(x,0.1,1);
		float alpha = ((float)(y-2))/((float)(SizeY-5));
		float speed = 3.f;
		if(Size.X>0.1f)
		{
			AMovingPlatform* NewPlatform  = GridActor->BuildMovingPlatform(BeginPos,EndPos,(SizeY-5)*(speed),
				Size,EMaterialSplat::Invisible,alpha,true);
			NewPlatform->SetPlatformMovement(EPlatformMovement::ForthTeleport);
		}
		BeginPos+=FVector(x+1,0,0);
		EndPos+=FVector(x+1,0,0);
		Size= FVector(SizeX-x-3,0.1,1);
		if(Size.X>0.1f)
		{
			AMovingPlatform* NewPlatform  = GridActor->BuildMovingPlatform(BeginPos,EndPos,(SizeY-5)*(speed),
				Size,EMaterialSplat::Invisible,alpha,true);
			NewPlatform->SetPlatformMovement(EPlatformMovement::ForthTeleport);
		}
	}
	return ExitVector;
}

