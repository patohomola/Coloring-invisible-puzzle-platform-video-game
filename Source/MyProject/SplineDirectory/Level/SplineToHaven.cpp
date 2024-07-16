// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineToHaven.h"


// Sets default values
ASplineToHaven::ASplineToHaven()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SplineGenerator = CreateDefaultSubobject<USplineGenerator>(TEXT("splineGenerator"));
}

// Called when the game starts or when spawned
void ASplineToHaven::BeginPlay()
{
	Super::BeginPlay();
	
}

FIntVector ASplineToHaven::GenerateRoom(FIntVector StartPos, int32 SizeX, int32 SizeY, int32 SizeZ)
{
	int Offset=0;
	FIntVector ExitVector;
	ARoom::Structure(StartPos,SizeX,SizeY,SizeZ,Offset,0,ExitVector,EHouseTheme::Normal);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	
	FVector Area =GridActor->GridCordToRealCord( FVector(((float)(SizeX-4)/2),((float)(SizeY-4)/2),0));
	
		
	FVector pos = GridActor->GridCordToRealCord((FVector)StartPos - FVector(Offset - ((float)SizeX/2),-((float)SizeY/2),-0.5));
	ASplineActor* newSplineActor = GetWorld()->SpawnActor<ASplineActor>(SplineActor,pos+FVector(0,0,30),FRotator::ZeroRotator,SpawnParams);
	
	SplineGenerator->SetSplineActor(newSplineActor);
	SplineGenerator->SetArea(FVector2f(Area.X,Area.Y));
	SplineGenerator->GenerateRandomTangle(10,500.f,0.0f, 0.0f);

	float x = (float)SizeX/2-1.25f;
	float y=2.3;//skip row

	FVector pos2=(FVector)((FVector)StartPos+FVector(1-Offset,y,0));
	FVector Size =FVector(x,0.1,1);
	if(Size.X>0.1f)
		GridActor->BuildPlatform(pos2,Size,EMaterialSplat::Visible);
	pos2+=FVector(x+0.6,0,0);
	Size= FVector(SizeX-x-2.6,0.1,1);
	if(Size.X>0.1f)
		GridActor->BuildPlatform(pos2,Size,EMaterialSplat::Visible);

	newSplineActor->UpdateMesh();
	
	return ExitVector;
}

