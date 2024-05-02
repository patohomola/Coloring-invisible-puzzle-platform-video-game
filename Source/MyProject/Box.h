#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"

// Enum for box sides
UENUM(BlueprintType)
enum class EBoxSide : uint8
{
    Front UMETA(DisplayName = "Front"),
    Back UMETA(DisplayName = "Back"),
    Left UMETA(DisplayName = "Left"),
    Right UMETA(DisplayName = "Right"),
    Top UMETA(DisplayName = "Top"),
    Bottom UMETA(DisplayName = "Bottom")
};

class MYPROJECT_API BoxComponent
{
public:
    // Constructor
    BoxComponent();

    // Method to set the box data
    void SetBoxData(const TArray<TArray<TArray<bool>>>& BoxData);

    // Method to get a specific side of the box as a 2D array
    TArray<TArray<bool>> GetBoxSide(EBoxSide Side) const;

    bool CompareSide(const BoxComponent& Other, EBoxSide Side) const;

    // Hash function for BoxComponent
    friend inline uint32 GetTypeHash(const BoxComponent& InBoxComponent)
    {
        // Implement a custom hash function based on your BoxData or other unique identifiers
        return FCrc::MemCrc32(&InBoxComponent, sizeof(InBoxComponent));
    }

    // Equality operator for BoxComponent (used for TMap key comparison)
    friend inline bool operator==(const BoxComponent& A, const BoxComponent& B)
    {
        // Implement an equality check based on your criteria (e.g., comparing BoxData)
        return A.BoxData == B.BoxData;
    }


private:
    TArray<TArray<TArray<bool>>> BoxData; // 3D array representing the box
};
