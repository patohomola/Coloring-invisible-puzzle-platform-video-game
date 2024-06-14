// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GroundPlatform.h"
#include "TimeAndScoreManager.h"
#include "Obstacle.generated.h"

UCLASS()
class MYPROJECT_API AObstacle : public AGroundPlatform
{
	GENERATED_BODY()
    ATimeAndScoreManager* TimeAndScoreManager;
	bool firsthit = false;
public:
	// Sets default values for this actor's properties
	AObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void FindTimeAndScoreManagers();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	UFUNCTION()
	void OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
