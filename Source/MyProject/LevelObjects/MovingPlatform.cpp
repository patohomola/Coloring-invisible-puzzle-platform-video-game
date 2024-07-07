// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElapsedTime = 0.0f;
	bIsMovingForward = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovingPlatform::SetState(float Alpha, bool bBool)
{
	ElapsedTime=Alpha*MoveDuration;
	bIsMovingForward=bBool;
}

void AMovingPlatform::BackAndForth(float DeltaTime)
{
	if (MoveDuration > 0)
	{
		ElapsedTime += DeltaTime;
		float Alpha = ElapsedTime / MoveDuration;

		if (bIsMovingForward)
		{
			SetActorLocation(FMath::Lerp(StartPosition, EndPosition, Alpha));

			if (Alpha >= 1.0f)
			{
				bIsMovingForward = false;
				ElapsedTime = ElapsedTime-MoveDuration;
			}
		}
		else
		{
			SetActorLocation(FMath::Lerp(EndPosition, StartPosition, Alpha));

			if (Alpha >= 1.0f)
			{
				bIsMovingForward = true;
				ElapsedTime = ElapsedTime-MoveDuration;
			}
		}
	}
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(PlatformMovement==EPlatformMovement::BackAndForth)
		BackAndForth(DeltaTime);

	else if(PlatformMovement==EPlatformMovement::ForthTeleport)
	{
		ElapsedTime += DeltaTime;
		float Alpha = ElapsedTime / MoveDuration;
		SetActorLocation(FMath::Lerp(StartPosition, EndPosition, Alpha));

		if (Alpha >= 1.0f)
		{
			ElapsedTime = ElapsedTime-MoveDuration;
		}
	}
}

