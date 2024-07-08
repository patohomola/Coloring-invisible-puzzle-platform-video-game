// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GroundPlatform.h"
#include "GameFramework/MovementComponent.h"
#include "MovingPlatform.generated.h"


UENUM(BlueprintType)
enum class EPlatformMovement : uint8
{
	BackAndForth,
	ForthTeleport
};

UCLASS()
class MYPROJECT_API AMovingPlatform : public AGroundPlatform
{
	GENERATED_BODY()

public:
	
	// Sets default values for this actor's properties
	AMovingPlatform();
	

	// The start and end positions
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector StartPosition;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector EndPosition;

	// Time to move from start to end
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveDuration;

	UPROPERTY(EditAnywhere, Category = "Movement")
	EPlatformMovement PlatformMovement;
	//UBoxComponent* BoxCollider;

	void SetPlatformMovement(EPlatformMovement newPlatformMovement)
	{
		this->PlatformMovement = newPlatformMovement;
	}

	void SetMovingPlatform(FVector newStartPosition,FVector newEndPosition, float newMoveDuration)
	{
		PlatformMovement=EPlatformMovement::BackAndForth;
		StartPosition=newStartPosition;
		EndPosition=newEndPosition;
		MoveDuration=newMoveDuration;
	}

	void SetState(float Alpha,bool bBool);
	void BackAndForth(float DeltaTime);

private:
	
	// Track the time
	float ElapsedTime;
	bool bIsMovingForward;
	
	// Function to update platform position
	void UpdatePlatformPosition(float DeltaTime);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
