// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Room.h"
#include "MyProject/SplineDirectory/SplineGenerator.h"
#include "SplineToHaven.generated.h"

UCLASS()
class MYPROJECT_API ASplineToHaven : public ARoom
{
public:
	virtual FIntVector GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ) override;

	UPROPERTY(EditAnywhere);
	TSubclassOf<ASplineActor> SplineActor;

private:
	USplineGenerator* SplineGenerator;

	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASplineToHaven();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:
	// Called every frame
};
