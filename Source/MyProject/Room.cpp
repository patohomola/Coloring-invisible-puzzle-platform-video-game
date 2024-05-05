// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"



// Sets default values
ARoom::ARoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ARoom::BeginPlay()
{
	GridActor->GetActorLocation();
	GenerateRoom(GetActorLocation(),10,10,10);
}


FVector ARoom::GenerateRoom(FVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	GridActor->BuildHouse(0,0,0,100);
	
	return StartPos;
}


