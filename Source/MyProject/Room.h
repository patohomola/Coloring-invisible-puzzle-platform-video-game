// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridActor.h"
#include "GroundPlatform.h"
#include "LevelObjects/SpawnManager.h"

#include "Room.generated.h"
//class AGridActor;

UCLASS()
class MYPROJECT_API ARoom : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	AGridActor* GridActor;
	
	ARoom();

	UFUNCTION(Blueprintable)
	virtual FIntVector GenerateRoom(FIntVector StartPos, int32 SizeX,int32 SizeY,int32 SizeZ);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void TownSquare(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ,int& Ofset,int Exit, FIntVector& exitVector,
	                EHouseTheme theme);
	bool Structure(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ, int& Ofset,int Exit, FIntVector& exitVector,
	               EHouseTheme theme);
};
