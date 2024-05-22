// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawner::SpawnObject(FVector Origin, FVector BoxExtent)
{
	FVector SpawnLocation = FMath::RandPointInBox(FBox(Origin,Origin+BoxExtent ));
	UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
	FRotator SpawnRotation = FRotator::ZeroRotator;
	if(ObjectToSpawn)
		GetWorld()->SpawnActor<AActor>(ObjectToSpawn, SpawnLocation, SpawnRotation);
}



