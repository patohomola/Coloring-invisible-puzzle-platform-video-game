// Fill out your copyright notice in the Description page of Project Settings.


#include "3DBlockTileComponent.h"


//not used

// Sets default values for this component's properties
U3DBlockTileComponent::U3DBlockTileComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void U3DBlockTileComponent::OnRegister()
{
	Super::OnRegister();

	// Draw cube corners based on voxel data
	for (int32 Index = 0; Index < VoxelData.Num(); ++Index)
	{
		int32 Z = Index/4;
		int32 XY=Index%4;
		int32 X=XY%2;
		int32 Y=XY/2;

		bVoxels[X][Y][Z]=VoxelData[Index];
		
		FVector CornerLocation =  FVector(X * 100.f, Y * 100.f, Z * 100.f);;

		// Determine sphere radius based on voxel value
		float SphereRadius = VoxelData[Index] ? 20.f : 10.f; // Adjust sizes as needed

		// Draw debug sphere
		DrawDebugSphere(GetWorld(), CornerLocation, SphereRadius, 12, FColor::White, false, 5.f, 0, 1.f);
	}
}


void U3DBlockTileComponent::Rotate90Degrees()
{
	// Rotate the block 90 degrees clockwise around the Y-axis (X and Z stay constant)
	bool RotatedVoxels[2][2][2];

	for (int X = 0; X < 2; ++X)
	{
		for (int Y = 0; Y < 2; ++Y)
		{
			for (int Z = 0; Z < 2; ++Z)
			{
				RotatedVoxels[Z][Y][1 - X] = bVoxels[X][Y][Z];
			}
		}
	}

	memcpy(bVoxels, RotatedVoxels, sizeof(bVoxels));
}

void U3DBlockTileComponent::MirrorX()
{
	// Mirror the block along the X-axis (Y and Z stay constant)
	bool MirroredVoxels[2][2][2];

	for (int X = 0; X < 2; ++X)
	{
		for (int Y = 0; Y < 2; ++Y)
		{
			for (int Z = 0; Z < 2; ++Z)
			{
				MirroredVoxels[1 - X][Y][Z] = bVoxels[X][Y][Z];
			}
		}
	}

	memcpy(bVoxels, MirroredVoxels, sizeof(bVoxels));
}

void U3DBlockTileComponent::MirrorY()
{
	// Mirror the block along the Y-axis (X and Z stay constant)
	bool MirroredVoxels[2][2][2];

	for (int X = 0; X < 2; ++X)
	{
		for (int Y = 0; Y < 2; ++Y)
		{
			for (int Z = 0; Z < 2; ++Z)
			{
				MirroredVoxels[X][1 - Y][Z] = bVoxels[X][Y][Z];
			}
		}
	}

	memcpy(bVoxels, MirroredVoxels, sizeof(bVoxels));
}



bool U3DBlockTileComponent::AreNotInConflict(const FIntVector& ThisLocation, const FIntVector& OtherLocation, U3DBlockTileComponent* OtherComponent) const
{
	if (!OtherComponent)
	{
		return false;
	}

	// Iterate over all corners (voxels) of this block
	for (int X = 0; X < 2; ++X)
	{
		for (int Y = 0; Y < 2; ++Y)
		{
			for (int Z = 0; Z < 2; ++Z)
			{
				FIntVector ThisCornerLocation = ThisLocation + FIntVector(X, Y, Z);

				// Check if voxel states match
				if (!OtherComponent->GetIsCornerFilled(OtherLocation,ThisCornerLocation,bVoxels[X][Y][Z]))
				{
					return false; // Corner mismatch, not matching
				}
			}
		}
	}
	return true;
}

bool U3DBlockTileComponent::GetIsCornerFilled(const FIntVector& ThisLocation, const FIntVector& CornerLocation,bool CornerValue)
{
	for (int X = 0; X < 2; ++X)
	{
		for (int Y = 0; Y < 2; ++Y)
		{
			for (int Z = 0; Z < 2; ++Z)
			{
				FIntVector ThisCornerLocation = ThisLocation + FIntVector(X, Y, Z);
				if(ThisCornerLocation==CornerLocation)
				{
					return (bVoxels[X][Y][Z]==CornerValue)?true:false;
				}
			}
		}
	}
	return true;
}
