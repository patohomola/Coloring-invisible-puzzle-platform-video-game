// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/SplineDirectory/SplineActor.h"
#include "PlatformSplineActor.generated.h"

UCLASS()
class MYPROJECT_API APlatformSplineActor : public ASplineActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlatformSplineActor();

	TArray<FVector> GetDistributedPointsOnSpline(float PartSize);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
