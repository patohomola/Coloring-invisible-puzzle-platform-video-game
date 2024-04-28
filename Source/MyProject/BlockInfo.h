// BlockInfo.h

#pragma once

#include "CoreMinimal.h"
#include "BlockInfo.generated.h"


UENUM(BlueprintType)
enum class EBlockOrientation : uint8
{
	North,
	East,
	South,
	West
};

USTRUCT(BlueprintType)
struct FBlockInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> BlockActor; // Mesh of the block (cube)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBlockOrientation Orientation; // Orientation of the block
};
