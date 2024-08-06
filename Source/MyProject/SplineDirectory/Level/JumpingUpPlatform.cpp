// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpingUpPlatform.h"


// Sets default values
AJumpingUpPlatform::AJumpingUpPlatform()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SplineGenerator = CreateDefaultSubobject<USplineGenerator>(TEXT("splineGenerator"));
}

// Called when the game starts or when spawned
void AJumpingUpPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJumpingUpPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FIntVector AJumpingUpPlatform::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int Offset=0;
	FIntVector ExitVector;
	ARoom::Structure(StartPos,SizeX,SizeY,SizeZ,Offset,0,ExitVector,EHouseTheme::Normal);
 
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	
	FVector Area =GridActor->GridCordToRealCord( FVector(((float)(SizeX-4)/2),((float)(SizeY-4)/2),0));
	
		
	FVector pos = GridActor->GridCordToRealCord((FVector)StartPos - FVector(Offset - ((float)SizeX/2),-((float)SizeY/2),-0.5));
	APlatformSplineActor* newSplineActor = GetWorld()->SpawnActor<APlatformSplineActor>(pos+FVector(0,0,30),FRotator::ZeroRotator,SpawnParams);
	USplineComponent* uspline = newSplineActor->GetSplineComponent();
	
	SplineGenerator->SetSplineActor(uspline);
	SplineGenerator->SetArea(FVector2f(Area.X,Area.Y));
	SplineGenerator->GenerateSlowlyElevatedLine(30000.f,0.2f);
	
	TArray<FVector> points= newSplineActor->GetDistributedPointsOnSpline(750.f);
	for (auto Point : points)
	{
		GridActor->BuildPlatform(GridActor->RealCordToGridCord(Point),FVector(1,1,0.1),EMaterialSplat::Visible);
	}

	
	return ExitVector;
}


