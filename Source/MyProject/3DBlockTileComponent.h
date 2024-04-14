// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/StaticArray.h"
#include "3DBlockTileComponent.generated.h"

UENUM(BlueprintType)
enum class EBooleanIndex : uint8
{
	Index000 UMETA(DisplayName = "000"),
	Index001 UMETA(DisplayName = "001"),
	Index010 UMETA(DisplayName = "010"),
	Index011 UMETA(DisplayName = "011"),
	Index100 UMETA(DisplayName = "100"),
	Index101 UMETA(DisplayName = "101"),
	Index110 UMETA(DisplayName = "110"),
	Index111 UMETA(DisplayName = "111")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API U3DBlockTileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	U3DBlockTileComponent();

	// Rotate the block 90 degrees clockwise around the Y-axis (X and Z stay constant)
	void Rotate90Degrees();

	// Mirror the block along the X-axis (Y and Z stay constant)
	void MirrorX();

	// Mirror the block along the Y-axis (X and Z stay constant)
	void MirrorY();

	bool AreNotInConflict(const FIntVector& ThisLocation, const FIntVector& OtherLocation, U3DBlockTileComponent* OtherComponent) const;

	bool GetIsCornerFilled(const FIntVector& ThisLocation, const FIntVector& CornerLocation, bool CornerValue);

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boolean Array")//, meta = (ClampMin = "8", ClampMax = "8"))
	TArray<bool> VoxelData={false,false,false,false,false,false,false,false}; // Pole boolean hodnôt veľkosti 
	
private:

	bool bVoxels[2][2][2];

protected:
	virtual void OnRegister() override;
};
