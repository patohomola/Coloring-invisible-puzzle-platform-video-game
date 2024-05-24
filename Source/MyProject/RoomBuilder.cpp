// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomBuilder.h"
#include  "LevelObjects/LevelExitTriggerBox.h"
#include "DrawDebugHelpers.h" 


// Sets default values
ARoomBuilder::ARoomBuilder()
{
	
}

// Called when the game starts or when spawned
void ARoomBuilder::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox=GetWorld()->SpawnActor<ALevelExitTriggerBox>(FVector::Zero(),FRotator::ZeroRotator);
	TriggerBox->RoomBuilder=this;
	CreateRandomRoom();
	CreateRandomRoom();
}

FRoomStruct SelectRandomRoom(const TArray<FRoomStruct>& RoomArray)
{
	// Calculate the total weight
	int32 TotalWeight = 0;
	for (const FRoomStruct& Room : RoomArray)
	{
		TotalWeight += Room.Weight;
	}

	// Generate a random number between 0 and TotalWeight
	int32 RandomValue = FMath::RandRange(0, TotalWeight - 1);

	// Select the struct based on the random value and cumulative weights
	int32 CumulativeWeight = 0;
	for (const FRoomStruct& Room : RoomArray)
	{
		CumulativeWeight += Room.Weight;
		if (RandomValue < CumulativeWeight)
		{
			return Room;
		}
	}

	// Fallback in case of error (should not happen)
	return RoomArray[0];
}

void ARoomBuilder::CreateRandomRoom()
{
	
	FRoomStruct RoomStruct = SelectRandomRoom(RoomStructs);
	ARoom* ChosenRoom =GetWorld()->SpawnActor<ARoom>(RoomStruct.Room,FVector(0,0,0),FRotator::ZeroRotator);
	//ARoom* ChosenRoom = RoomArray[RandomIndex];

	// Check if the chosen room is valid
	if (ChosenRoom)
	{
		if(!GridActor)
			return;
		ChosenRoom->GridActor=GridActor;
		// Call the GenerateRoom method
		FIntVector StartPos = Road; // Define your StartPos
		int32 SizeX = FMath::RandRange((int)RoomStruct.XRange.GetMin(),(int)RoomStruct.XRange.GetMax()); // Define SizeX
		int32 SizeY = FMath::RandRange((int)RoomStruct.YRange.GetMin(),(int)RoomStruct.YRange.GetMax()); // Define SizeY
		int32 SizeZ = FMath::RandRange((int)RoomStruct.ZRange.GetMin(),(int)RoomStruct.ZRange.GetMax()); // Define SizeZ
		Road= ChosenRoom->GenerateRoom(StartPos, SizeX, SizeY, SizeZ);
		FVector Location=FVector(Road)*FVector(GridActor->ElementSpacing,GridActor->ElementSpacing,GridActor->ElementHeightSpacing);
		Location+=FVector(-100.f,-100.f,100.f);
		Location+=GridActor->GetTransform().GetLocation();
		TriggerBox->SetActorLocation(Location);
		TriggerBox->isActive=true;
		float Radius = 1000.0f;
		FColor Color = FColor::Red;
		bool bPersistentLines = true; // Set to true if you want the lines to persist, false for temporary
		float LifeTime = -1.0f; // Lifetime of the debug sphere (-1 means infinite)
		uint8 DepthPriority = 0; // Default depth priority
		float Thickness = 2.0f; // Thickness of the lines

		DrawDebugSphere(GetWorld(), Location, Radius, 12, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
	}
}

