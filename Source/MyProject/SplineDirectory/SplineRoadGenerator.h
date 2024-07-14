// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineActor.h"
#include "SplineRoadGenerator.generated.h"


UCLASS()
class MYPROJECT_API ASplineRoadGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineRoadGenerator();

	UPROPERTY(EditAnywhere)
	ASplineActor* SplineActor;
 
	void ModifySplineActor();
	void GenerateRandomTangle(int32 NumberOfPoints, float minDist, float Start, float Exit);
	FVector GetRandomPointWithinBounds(float AreaSizeX, float AreaSizeY) const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
	virtual void Tick(float DeltaTime) override;

};
