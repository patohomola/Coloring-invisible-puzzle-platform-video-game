// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESpawnSetting : uint8
{
	Default UMETA(DisplayName = "Default"),
	MoreAmmo UMETA(DisplayName = "MoreAmmo")
};


USTRUCT(BlueprintType)
struct FRoomSpawnStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room Struct")
	ESpawnSetting Room;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room Struct")
	float density = 0.2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room Struct")
	TArray<int32> ObjectWeights;
};


UCLASS()
class MYPROJECT_API ASpawnManager : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	TMap<ESpawnSetting,FRoomSpawnStruct> RoomSpawnStructs;

public:
	ASpawnManager();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> Ammo;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> ScoreBottle;

	UPROPERTY(EditAnywhere, Category = "Spawning")	
	TArray<TSubclassOf<AActor>> SpawnObjects;

public:
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PopulateArea(FVector Origin, FVector BoxExtent, ESpawnSetting Name);
};
