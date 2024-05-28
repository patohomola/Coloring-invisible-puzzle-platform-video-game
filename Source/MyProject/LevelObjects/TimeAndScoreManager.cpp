// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeAndScoreManager.h"


// Sets default values
ATimeAndScoreManager::ATimeAndScoreManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATimeAndScoreManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimeAndScoreManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATimeAndScoreManager::AddTime_Implementation(int32 InputValue)
{
	
}


