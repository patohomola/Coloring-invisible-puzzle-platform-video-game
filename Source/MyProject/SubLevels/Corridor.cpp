// Fill out your copyright notice in the Description page of Project Settings.


#include "Corridor.h"

//#include "IContentBrowserSingleton.h"


// Sets default values
ACorridor::ACorridor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

// Called when the game starts or when spawned
void ACorridor::BeginPlay()
{
	Super::BeginPlay();
	
}

FIntVector ACorridor::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	return Super::GenerateRoom(StartPos, 3, 5, 5);
}


