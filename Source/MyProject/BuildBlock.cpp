// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildBlock.h"

// Sets default values
ABuildBlock::ABuildBlock()
{
	// Set up the mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	RootComponent = BlockMesh;
}

// Called when the game starts or when spawned
void ABuildBlock::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABuildBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Method to initialize the block
void ABuildBlock::InitializeBlock()
{
	if (BlockMaterials.Num() > 0 && BlockMesh)
	{
		// Set the material of the mesh to a random material from the list
		BlockMesh->SetMaterial(0, GetRandomMaterial());
	}
}

// Method to select a random material from the list
UMaterialInterface* ABuildBlock::GetRandomMaterial()
{
	if (BlockMaterials.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, BlockMaterials.Num() - 1);
		return BlockMaterials[RandomIndex];
	}
	return nullptr;
}

void ABuildBlock::RandomRotateBlock()
{
	if (BlockMesh)
	{
		FRotator NewRotation = FRotator(0, FMath::RandRange(0, 3) * 90, 0);
		BlockMesh->SetRelativeRotation(NewRotation);
	}
}