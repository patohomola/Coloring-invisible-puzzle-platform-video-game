// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridActor.h"

#include "Room.generated.h"


UCLASS()
class MYPROJECT_API ARoom : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	AGridActor* GridActor;
	
	ARoom();

	UFUNCTION(Blueprintable)
	FVector GenerateRoom(FVector StartPos, int32 SizeX,int32 SizeY,int32 SizeZ);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
