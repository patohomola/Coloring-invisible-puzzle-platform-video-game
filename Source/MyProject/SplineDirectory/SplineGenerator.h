// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SplineRoadGenerator.h"
#include "Components/ActorComponent.h"
#include "SplineGenerator.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT_API USplineGenerator : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USplineGenerator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	void MakeSlowlyEleveated(USplineComponent* SplineComponent, float koefiecient);
	void CalculateTangent(USplineComponent* SplineComponent, int32 i);
	void calculateStartTangent(USplineComponent* SplineComponent);
	void calculateEndTangent(USplineComponent* SplineComponent);
	void CalculateTangents(USplineComponent* SplineComponent);
	void GenerateSlowlyElevatedLine(float Size, float koeficient);
	void GenerateRandomTangle(int32 NumberOfPoints, float minDist, float Start, float Exit);
	FVector GetRandomPointWithinBounds(float AreaSizeX, float AreaSizeY) const;
	void SubdivideSpline(USplineComponent* SplineComponent);
	float CalculateShortestDistanceBetweenSplineSegments(int32 SegmentIndex1, int32 SegmentIndex2, USplineComponent* SplineComponent) const;

public:	
	// Sets default values for this actor's properties

	UPROPERTY(EditAnywhere)
	USplineComponent* SplineActor;

private:
	FVector2f Area;


public:
	void SetSplineActor(USplineComponent* newSplineActor)
	{
		this->SplineActor = newSplineActor;
	}

	void SetArea(const FVector2f& newArea)
	{
		this->Area = newArea;
	}
	UPROPERTY(EditAnywhere)
	float Diameter=500.f;
	// Called every frame
};
