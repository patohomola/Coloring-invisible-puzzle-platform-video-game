﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Room.h"
#include "HighWire.generated.h"

UCLASS()
class MYPROJECT_API AHighWire : public ARoom
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHighWire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual FIntVector GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ) override;
};
