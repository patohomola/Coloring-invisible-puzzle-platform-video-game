// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include  "Room.h"
#include  "GridActor.h"
//#include "LevelObjects/LevelExitTriggerBox.h"
#include "LevelObjects/TimeAndScoreManager.h"
class ALevelExitTriggerBox;
#include "RoomBuilder.generated.h"


USTRUCT(BlueprintType)
struct FRoomStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room Struct")
	TSubclassOf<ARoom> Room;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room Struct", meta=(ClampMin="1"))
	int32 Weight=1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room Struct", meta=(ClampMin="1"))
	int32 Time=1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room Struct",
		meta=(DisplayName="X Range", ClampMin="3", UIMin="3", ClampMax="1000", UIMax="1000"))
	FVector2D XRange = FVector2D(10.0f, 20.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room Struct",
		meta=(DisplayName="Y Range", ClampMin="3", UIMin="3", ClampMax="1000", UIMax="1000"))
	FVector2D YRange = FVector2D(10.0f, 20.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Room Struct",
		meta=(DisplayName="Z Range", ClampMin="3", UIMin="3", ClampMax="1000", UIMax="1000"))
	FVector2D ZRange = FVector2D(5, 3);
};

UCLASS()
class MYPROJECT_API ARoomBuilder : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoomBuilder();

	ALevelExitTriggerBox* TriggerBox;

	UPROPERTY(EditAnywhere) 
	FIntVector Road = FIntVector(0,0,0);

	UPROPERTY(EditAnywhere)
	AGridActor* GridActor;

	/*UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ARoom>> RoomArray;*/

	UPROPERTY(EditAnywhere)
	TArray<FRoomStruct> RoomStructs;

	UPROPERTY(EditAnywhere)
	ATimeAndScoreManager* TimeScoreManger;
	
	UFUNCTION(BlueprintCallable)
	void CreateRandomRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
