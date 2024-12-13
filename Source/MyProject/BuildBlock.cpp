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
void ABuildBlock::InitializeBlock(EHouseTheme Theme)
{
	TArray<class UMaterialInterface*> Materials;
	switch (Theme)
	{
	case EHouseTheme::Normal:
		Materials=BlockMaterials;
		break;
	case EHouseTheme::Blank:
		Materials=BlockMaterialsCleanCanvas;
		break;
	case EHouseTheme::Transparent:
		Materials=BlockMaterialsInvincible;
	}
	
	if (Materials.Num() > 0 && BlockMesh)
	{
		int32 RandomIndex = FMath::RandRange(0, Materials.Num() - 1);
		// Set the material of the mesh to a random material from the list
		BlockMesh->SetMaterial(0, Materials[RandomIndex]);
	}
}

// Method to select a random material from the list
UMaterialInterface* ABuildBlock::GetRandomMaterial()
{
	/*if (BlockMaterials.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, BlockMaterials.Num() - 1);
		return BlockMaterials[RandomIndex];
	}*/
	
	if (BlockMaterialsCleanCanvas.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, BlockMaterialsCleanCanvas.Num() - 1);
		return BlockMaterialsCleanCanvas[RandomIndex];
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

