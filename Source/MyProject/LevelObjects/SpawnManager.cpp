// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"

#include "Kismet/KismetMathLibrary.h"

ASpawnManager::ASpawnManager()
{
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
}

void ASpawnManager::PopulateArea(FVector Origin, FVector BoxExtent, ESpawnSetting Name)
{
	FRoomSpawnStruct object= RoomSpawnStructs[Name];
	int  n = BoxExtent.X/1000*BoxExtent.Y/1000*BoxExtent.Z/1000 * object.density; 

	int32 TotalSum=0;
	TArray<int32> MapToIndex;
	for (int32 num: object.ObjectWeights)
	{
		TotalSum+=num;
		MapToIndex.Add(TotalSum);
	}
	MapToIndex.Add(TotalSum+10);

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("number of ammo %d"), n));
	for (int i = 0; i < n; ++i)
	{
		
		FVector SpawnLocation = FMath::RandPointInBox(FBox(Origin,Origin+BoxExtent ));
		UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
		FRotator SpawnRotation = FRotator::ZeroRotator;
		
		int32 RandomValue = FMath::RandRange(0, TotalSum - 1);

		int32 index =0;
		while (RandomValue>=MapToIndex[index])
		{
			index++;
		}
		
		//if(SpawnObjects[index])
			GetWorld()->SpawnActor<AActor>(SpawnObjects[index], SpawnLocation, SpawnRotation);
	}
}
