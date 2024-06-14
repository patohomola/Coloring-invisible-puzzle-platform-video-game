// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstacle::AObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Bind the hit event
	firsthit=true;
	AGroundPlatform::PlatformMesh->OnComponentHit.AddDynamic(this, &AObstacle::OnObstacleHit);
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	FindTimeAndScoreManagers();
	
	
}
void AObstacle::FindTimeAndScoreManagers()
{
	// Array to hold the found actors
	TArray<AActor*> FoundActors;

	// Get all actors of class ATimeAndScoreManager
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATimeAndScoreManager::StaticClass(), FoundActors);

	// If any TimeAndScoreManager actors were found, store the first one in the TimeAndScoreManager variable
	if (FoundActors.Num() > 0)
	{
		TimeAndScoreManager = Cast<ATimeAndScoreManager>(FoundActors[0]);
		if (TimeAndScoreManager)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found TimeAndScoreManager: %s"), *TimeAndScoreManager->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Found an actor but it is not a TimeAndScoreManager"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No TimeAndScoreManager found in the scene"));
	}
}


// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObstacle::OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (OtherActor && Character && firsthit)
	{
		firsthit=false;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ObstacleHit!"));
		if (TimeAndScoreManager)
		{
			TimeAndScoreManager->GameOver(1);
			// Call some function on TimeAndScoreManager, for example:
			// TimeAndScoreManager->AddScore(10);
		}
	}
}


