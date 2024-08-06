// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Room.h"
#include "MyProject/SplineDirectory/PlatformSplineActor.h"
#include "MyProject/SplineDirectory/SplineGenerator.h"
#include "JumpingUpPlatform.generated.h"

UCLASS()
class MYPROJECT_API AJumpingUpPlatform : public ARoom
{
	GENERATED_BODY()
private:
	//UPROPERTY(EditAnywhere);
	//TSubclassOf<APlatformSplineActor> PlatformSplineActor;
	USplineGenerator* SplineGenerator;
public:
	// Sets default values for this actor's properties
	AJumpingUpPlatform();
	virtual FIntVector GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
