﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include  "Room.h"
#include  "GridActor.h"
#include "RoomBuilder.generated.h"

UCLASS()
class MYPROJECT_API ARoomBuilder : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoomBuilder();

	UPROPERTY(EditAnywhere) 
	FIntVector Road = FIntVector(0,0,0);

	UPROPERTY(EditAnywhere)
	AGridActor* GridActor;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ARoom>> RoomArray;

	UFUNCTION(BlueprintCallable)
	void CreateRandomRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
