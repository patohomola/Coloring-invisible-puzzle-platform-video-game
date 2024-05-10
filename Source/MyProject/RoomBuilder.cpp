// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomBuilder.h"


// Sets default values
ARoomBuilder::ARoomBuilder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARoomBuilder::BeginPlay()
{
	Super::BeginPlay();
	CreateRandomRoom();
	CreateRandomRoom();
}

void ARoomBuilder::CreateRandomRoom()
{
	int32 RandomIndex = FMath::RandRange(0, RoomArray.Num() - 1);
	ARoom* ChosenRoom =GetWorld()->SpawnActor<ARoom>(RoomArray[RandomIndex],FVector(0,0,0),FRotator::ZeroRotator);
	//ARoom* ChosenRoom = RoomArray[RandomIndex];

	// Check if the chosen room is valid
	if (ChosenRoom)
	{
		if(!GridActor)
			return;
		ChosenRoom->GridActor=GridActor;
		// Call the GenerateRoom method
		FIntVector StartPos = Road; // Define your StartPos
		int32 SizeX = FMath::RandRange(8,16); // Define SizeX
		int32 SizeY = FMath::RandRange(8,16); // Define SizeY
		int32 SizeZ = FMath::RandRange(8,16); // Define SizeZ
		Road= ChosenRoom->GenerateRoom(StartPos, SizeX, SizeY, SizeZ);
                
		// Do something with the generated room
	}
}

