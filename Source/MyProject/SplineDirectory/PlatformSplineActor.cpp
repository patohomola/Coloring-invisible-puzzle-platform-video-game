// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformSplineActor.h"


// Sets default values
APlatformSplineActor::APlatformSplineActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APlatformSplineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformSplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


TArray<FVector> APlatformSplineActor::GetDistributedPointsOnSpline(float PartSize)
{
	int32 partCount = ((float)SplineComponent->GetSplineLength()/PartSize);
	TArray<FVector> locations;
	for (int i = 0; i < partCount; ++i)
	{
		FVector newLocation = SplineComponent->GetLocationAtDistanceAlongSpline((float)i*PartSize,ESplineCoordinateSpace::World);
		locations.Add(newLocation);
	}
	return locations;
}