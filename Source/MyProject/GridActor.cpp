// GridActor.cpp

#include "GridActor.h"



//#include "Runtime/TraceLog/standalone_epilogue.h"

// Sets default values
AGridActor::AGridActor()
{
	// Set default values
	NumRows = 5;
	NumColumns = 5;
	NumLayers = 5;
	ElementSpacing = 600.0f;
	ElementHeightSpacing = 300.0f;

	// Set up the root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void AGridActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Generate the grid when the game starts
	//GenerateGrid();
}



// Method to generate the 3D grid and spawn block actors
void AGridActor::GenerateGrid()
{
	// Spawn block actors at random locations in the grid
	
	for (int32 Row = 0; Row < NumRows; ++Row)
	{
		BuildHouse(Row,0,0,FMath::RandRange(3,NumLayers), EHouseTheme::Blank);
		BuildHouse(Row,NumColumns-1,0,FMath::RandRange(3,NumLayers), EHouseTheme::Blank);
	}
	for (int32 Column = 1; Column < NumColumns-1; ++Column)
	{
		BuildHouse(0,Column,0,FMath::RandRange(3,NumLayers), EHouseTheme::Blank);
		BuildHouse(NumRows-1,Column,0,FMath::RandRange(3,NumLayers), EHouseTheme::Blank);
	}
}

void AGridActor::BuildHouse(int32 X, int32 Y, int32 Z, int32 Height, EHouseTheme Theme)
{
	if (GroundBlockActorClasses.Num() == 0 || FloorBlockActorClasses.Num() == 0 || RoofBlockActorClasses.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Block actor classes are not set."));
		return;
	}

	FVector StartLocation = GetActorLocation()+FVector(X * ElementSpacing, Y * ElementSpacing, Z*ElementHeightSpacing);
	FRotator Rotation = FRotator::ZeroRotator;

	for (int32 Layer = 0; Layer < Height; ++Layer)
	{
		// Calculate spawn location
		FVector SpawnLocation = StartLocation + FVector(0, 0, Layer * ElementHeightSpacing);

		// Choose block actor class based on the layer
		TSubclassOf<ABuildBlock> BlockActorClass;
		if (Layer == 0)
		{
			// Ground floor
			BlockActorClass = GroundBlockActorClasses.Num() > 0 ? GroundBlockActorClasses[FMath::RandRange(0, GroundBlockActorClasses.Num() - 1)] : nullptr;
		}
		else if (Layer == Height - 1)
		{
			// Roof
			BlockActorClass = RoofBlockActorClasses.Num() > 0 ? RoofBlockActorClasses[FMath::RandRange(0, RoofBlockActorClasses.Num() - 1)] : nullptr;
		}
		else
		{
			// Middle layers (floor)
			BlockActorClass = FloorBlockActorClasses.Num() > 0 ? FloorBlockActorClasses[FMath::RandRange(0, FloorBlockActorClasses.Num() - 1)] : nullptr;
		}

		// Spawn block actor
		if (BlockActorClass)
		{
			ABuildBlock* NewBlockActor = GetWorld()->SpawnActor<ABuildBlock>(BlockActorClass, SpawnLocation, Rotation);
			if (NewBlockActor)
			{
				NewBlockActor->InitializeBlock(Theme);
				NewBlockActor->RandomRotateBlock();
				SpawnedBlocks.Add(NewBlockActor);
			}
		}
	}
}

FVector AGridActor::GridCordToRealCord(FVector position)
{
	position-=FVector(0.5f,0.5f,0);
	return GetActorLocation()+
		FVector(position.X * ElementSpacing,
				position.Y * ElementSpacing,
				position.Z*ElementHeightSpacing);
}

FVector AGridActor::RealCordToGridCord(FVector realPosition)
{
	FVector actorLocation = GetActorLocation();
	realPosition -= actorLocation; // Subtract the actor's location
	FVector position(realPosition.X / ElementSpacing,
					 realPosition.Y / ElementSpacing,
					 realPosition.Z / ElementHeightSpacing);
	position += FVector(0.5f, 0.5f, 0); // Shift back
	return position;
}

void AGridActor::GridtoWordCordinate(FVector position, FVector scalingFactor, FVector& SpawnLocation, FVector& Scale)
{
	SpawnLocation=GridCordToRealCord(position);
	Scale = FVector(scalingFactor.X * ElementSpacing,
	                scalingFactor.Y * ElementSpacing, scalingFactor.Z*ElementHeightSpacing);
}

void AGridActor::BuildPlatform(FVector position, FVector scalingFactor, EMaterialSplat type)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector SpawnLocation;
	FRotator SpawnRotation= FRotator::ZeroRotator;
	FVector Scale;
	GridtoWordCordinate(position, scalingFactor, SpawnLocation, Scale);
	Scale/=100;
	// Spawn the platform
	
	AGroundPlatform* NewPlatform = GetWorld()->SpawnActor<AGroundPlatform>(GroundPlatform, SpawnLocation, SpawnRotation, SpawnParams);

	if (NewPlatform)
	{
		// Initialize platform size (example size)
		NewPlatform->InitializePlatform(Scale);
		NewPlatform->setMaterialByType(type);
	}
}


AMovingPlatform* AGridActor::BuildMovingPlatform(FVector StartPosition, FVector EndPosition, float Duration,
                                                 FVector scalingFactor, EMaterialSplat type)
{
	return BuildMovingPlatform(StartPosition,EndPosition,Duration,scalingFactor,type,0.f,true);
}

AMovingPlatform* AGridActor::BuildMovingPlatform(FVector StartPosition, FVector EndPosition, float Duration, FVector scalingFactor, EMaterialSplat type, float Alpha, bool bMovingForward)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	
	StartPosition = GridCordToRealCord(StartPosition);
	EndPosition=GridCordToRealCord(EndPosition);
	FRotator SpawnRotation= FRotator::ZeroRotator;
	FVector Scale=FVector(scalingFactor.X * ElementSpacing,
					scalingFactor.Y * ElementSpacing, scalingFactor.Z * ElementHeightSpacing);
	Scale/=100;
	// Spawn the platform
	
	AMovingPlatform* NewPlatform = GetWorld()->SpawnActor<AMovingPlatform>(MovingPlatform, StartPosition, SpawnRotation, SpawnParams);

	if (NewPlatform)
	{
		// Initialize platform size (example size)
		NewPlatform->SetMovingPlatform(StartPosition,EndPosition,Duration);
		NewPlatform->InitializePlatform(Scale);
		NewPlatform->setMaterialByType(type);
	}
	
	NewPlatform->SetState(Alpha,bMovingForward);
	return NewPlatform;
}

void AGridActor::BuildObstacle(FVector position, FVector scalingFactor)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	
	position=GridCordToRealCord(position);
	FRotator SpawnRotation= FRotator::ZeroRotator;
	FVector Scale=FVector(scalingFactor.X * ElementSpacing,
					scalingFactor.Y * ElementSpacing, scalingFactor.Z * ElementHeightSpacing);
	Scale/=100;
	// Spawn the platform
	
	AObstacle* NewPlatform = GetWorld()->SpawnActor<AObstacle>(Obstacle, position, SpawnRotation, SpawnParams);
	
	if (NewPlatform)
	{
		// Initialize platform size (example size)
		NewPlatform->InitializePlatform(Scale);
		NewPlatform->setMaterialByType(EMaterialSplat::Invisible);
	}
}



void AGridActor::SpawnAmmoInSpawnBlockInGrid(FVector position, FVector scalingFactor, int count)
{
	FVector SpawnLocation;
	FVector Scale;
	GridtoWordCordinate(position,scalingFactor,SpawnLocation,Scale);
	for (int i = 0; i < count; ++i)
	{
		Spawner->SpawnObject(SpawnLocation,Scale);
	}
}

void AGridActor::SpawnAmmoInSpawnBlock(FVector position, FVector scalingFactor, int count)
{
	position-=FVector(0.5f,0.5f,0);
	for (int i = 0; i < count; ++i)
	{
		Spawner->SpawnObject(position,scalingFactor);
	}
}



void AGridActor::BuildHouse(FIntVector position, int32 Height, EHouseTheme Theme)
{
	BuildHouse(position.X,position.Y,position.Z,Height, Theme);	
}