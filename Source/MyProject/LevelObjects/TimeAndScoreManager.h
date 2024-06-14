// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeAndScoreManager.generated.h"

UCLASS()
class MYPROJECT_API ATimeAndScoreManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATimeAndScoreManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void AddTime(int32 InputValue);
	virtual void AddTime_Implementation(int32 InputValue);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void AddLevel(int32 InputValue);
	virtual void AddLevel_Implementation(int32 InputValue);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void AddScore(int32 InputValue);
	virtual void AddScore_Implementation(int32 InputValue);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void GameOver(int32 InputValue);
	virtual void GameOver_Implementation(int32 InputValue);
};
