// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Room.h"
#include "MovingPlatformRoom.generated.h"

UCLASS()
class MYPROJECT_API AMovingPlatformRoom : public ARoom
{
	GENERATED_BODY()
protected:
	void BuildMovingPlatformAtRandom(FVector StartPosition,FVector EndPosition,float Duration, FVector scalingFactor, EMaterialSplat type);
public:
	// Sets default values for this actor's properties
	AMovingPlatformRoom();

	virtual FIntVector GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ) override;

	

protected:
	// Called when the game starts or when spawned

public:
	// Called every frame
};
