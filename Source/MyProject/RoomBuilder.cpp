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

		// Do something with the generated room
	}
}

