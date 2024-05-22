// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class MYPROJECT_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawner();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnObject(FVector Origin, FVector BoxExtent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> ObjectToSpawn;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
