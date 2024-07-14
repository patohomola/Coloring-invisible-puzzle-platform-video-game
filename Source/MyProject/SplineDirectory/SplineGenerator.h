﻿// Fill out your copyright notice in the Description page of Project Settings.

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
	void GenerateRandomTangle(int32 NumberOfPoints, float minDist, float Start, float Exit);
	FVector GetRandomPointWithinBounds(float AreaSizeX, float AreaSizeY) const;

public:	
	// Sets default values for this actor's properties

	UPROPERTY(EditAnywhere)
	ASplineActor* SplineActor;

private:
	FVector2f Area;

public:
	void SetSplineActor(ASplineActor* newSplineActor)
	{
		this->SplineActor = newSplineActor;
	}

	void SetArea(const FVector2f& newArea)
	{
		this->Area = newArea;
	}

	// Called every frame
};