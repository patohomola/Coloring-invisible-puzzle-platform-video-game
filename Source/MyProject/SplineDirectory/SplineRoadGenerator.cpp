// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineRoadGenerator.h"

// Sets default values
ASplineRoadGenerator::ASplineRoadGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

// Called when the game starts or when spawned
void ASplineRoadGenerator::BeginPlay()
{
	Super::BeginPlay();
	//ModifySplineActor();
}

// Called every frame
void ASplineRoadGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASplineRoadGenerator::ModifySplineActor()
{
	if (SplineActor)
	{
		// Get the SplineComponent
		USplineComponent* SplineComp = SplineActor->GetSplineComponent();

		SetArea(FVector2f(2000.f,2000.f));
		GenerateRandomTangle(10,100.f,0.0f, 0.0f);
		
		// Modify the SplineComponent as needed
		// Example: Add a new spline point
		//SplineComp->AddSplinePoint(FVector(100, 100, 0), ESplineCoordinateSpace::Local);

		// You can also replace the SplineComponent entirely if needed
		// USplineComponent* NewSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("NewSplineComponent"));
		// SplineActor->SetSplineComponent(NewSplineComponent);

		SplineActor->UpdateMesh();
	}
}


void ASplineRoadGenerator::GenerateRandomTangle( int32 NumberOfPoints,float minDist, float Start, float Exit)
{
	USplineComponent* SplineComponent = SplineActor->GetSplineComponent();
	SplineComponent->ClearSplinePoints(false);

	TArray<FVector> Points;
	
	
	// Generate random points within bounds
	FVector lastpoint= FVector(Start,-Area.Y,0.f);
	Points.Add(lastpoint - FVector(0,10,0));
	FVector newPoint = lastpoint;
	for (int32 i = 0; i < NumberOfPoints; ++i)
	{
		Points.Add(newPoint);
		while (FVector::Dist(lastpoint,newPoint)<minDist)
		{
			newPoint =GetRandomPointWithinBounds(Area.X, Area.Y);
		}
		
		lastpoint=newPoint;
	}
	Points.Add(newPoint);
	Points.Add(FVector(Exit,Area.Y,0.f));
	Points.Add(FVector(Exit,Area.Y+10,0.f));

	// Add points to the spline
	for (int32 i = 0; i < Points.Num(); ++i)
	{
		SplineComponent->AddSplinePoint(Points[i], ESplineCoordinateSpace::Local, false);
	}

	// Calculate tangents to minimize curvature
	for (int32 i = 1; i < Points.Num() - 1; ++i)
	{
		FVector PreviousPoint = Points[i - 1];
		FVector CurrentPoint = Points[i];
		FVector NextPoint = Points[i + 1];

		FVector Dir = FVector(0,0,0);

		Dir += (PreviousPoint-CurrentPoint).GetSafeNormal();
		Dir -=  (NextPoint-CurrentPoint).GetSafeNormal();
		Dir = Dir.GetSafeNormal();
		// Calculate the distance for the control points
		float DistanceToPrev = FVector::Dist(PreviousPoint, CurrentPoint);
		float DistanceToNext = FVector::Dist(CurrentPoint, NextPoint);

		FVector ArriveTangent = Dir * DistanceToPrev * -1.f;
		FVector LeaveTangent = Dir * DistanceToNext * -1.f;

		SplineComponent->SetTangentsAtSplinePoint(i, ArriveTangent, LeaveTangent, ESplineCoordinateSpace::Local);
	}

	// Set tangents for the first and last points
	if (Points.Num() > 1)
	{
		FVector FirstTangent = (Points[1] - Points[0]) / 2.0f;
		SplineComponent->SetTangentsAtSplinePoint(0, FirstTangent, FirstTangent, ESplineCoordinateSpace::Local);

		FVector LastTangent = (Points[Points.Num() - 1] - Points[Points.Num() - 2]) / 2.0f;
		SplineComponent->SetTangentsAtSplinePoint(Points.Num() - 1, LastTangent, LastTangent, ESplineCoordinateSpace::Local);
	}

	SplineComponent->UpdateSpline();
	
	// Adjust Z coordinate proportionally based on distance along the spline
	for (int32 i = 0; i < SplineComponent->GetNumberOfSplinePoints(); ++i)
	{
		float Distance = SplineComponent->GetDistanceAlongSplineAtSplinePoint(i);
		FVector Point = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		Point.Z = Distance *0.15f;  // Adjust Z proportionally
		SplineComponent->SetLocationAtSplinePoint(i, Point, ESplineCoordinateSpace::Local, false);
	}

	SplineComponent->UpdateSpline();	

}

FVector ASplineRoadGenerator::GetRandomPointWithinBounds(float AreaSizeX,float AreaSizeY) const
{
	return FVector(
		FMath::FRandRange(-AreaSizeX, AreaSizeX),
		FMath::FRandRange(-AreaSizeY, AreaSizeY),
		0.0f
	);
}

