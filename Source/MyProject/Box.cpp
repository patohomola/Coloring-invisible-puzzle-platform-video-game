#include "Box.h"

BoxComponent::BoxComponent()
{
    // Initialize variables if needed
}

void BoxComponent::SetBoxData(const TArray<TArray<TArray<bool>>>& InBoxData)
{
    BoxData = InBoxData;
}

TArray<TArray<bool>> BoxComponent::GetBoxSide(EBoxSide Side) const
{
    const int32 Width = BoxData.Num();
    const int32 Height = BoxData[0].Num();
    const int32 Depth = BoxData[0][0].Num();
    
    TArray<TArray<bool>> Result;

    switch (Side)
    {
    case EBoxSide::Front:
        Result.Init(TArray<bool>(), Height);
        for (int32 Y = 0; Y < Height; ++Y)
        {
            Result[Y].Init(false, Width);
            for (int32 X = 0; X < Width; ++X)
            {
                Result[Y][X] = BoxData[X][Y][0];
            }
        }
        break;

    case EBoxSide::Back:
        Result.Init(TArray<bool>(), Height);
        for (int32 Y = 0; Y < Height; ++Y)
        {
            Result[Y].Init(false, Width);
            for (int32 X = 0; X < Width; ++X)
            {
                Result[Y][X] = BoxData[X][Y][Depth - 1];
            }
        }
        break;

    case EBoxSide::Left:
        Result.Init(TArray<bool>(), Depth);
        for (int32 Z = 0; Z < Depth; ++Z)
        {
            Result[Z].Init(false, Height);
            for (int32 Y = 0; Y < Height; ++Y)
            {
                Result[Z][Y] = BoxData[0][Y][Z];
            }
        }
        break;

    case EBoxSide::Right:
        Result.Init(TArray<bool>(), Depth);
        for (int32 Z = 0; Z < Depth; ++Z)
        {
            Result[Z].Init(false, Height);
            for (int32 Y = 0; Y < Height; ++Y)
            {
                Result[Z][Y] = BoxData[Width - 1][Y][Z];
            }
        }
        break;

    case EBoxSide::Top:
        Result.Init(TArray<bool>(), Width);
        for (int32 X = 0; X < Width; ++X)
        {
            Result[X].Init(false, Depth);
            for (int32 Z = 0; Z < Depth; ++Z)
            {
                Result[X][Z] = BoxData[X][0][Z];
            }
        }
        break;

    case EBoxSide::Bottom:
        Result.Init(TArray<bool>(), Width);
        for (int32 X = 0; X < Width; ++X)
        {
            Result[X].Init(false, Depth);
            for (int32 Z = 0; Z < Depth; ++Z)
            {
                Result[X][Z] = BoxData[X][Height - 1][Z];
            }
        }
        break;

    default:
        UE_LOG(LogTemp, Warning, TEXT("Invalid box side requested!"));
        break;
    }

    return Result;
}

bool BoxComponent::CompareSide(const BoxComponent& Other, EBoxSide Side) const
{
    // Determine the opposite side based on the specified side
    EBoxSide OppositeSide;

    switch (Side)
    {
    case EBoxSide::Front:
        OppositeSide = EBoxSide::Back;
        break;
    case EBoxSide::Back:
        OppositeSide = EBoxSide::Front;
        break;
    case EBoxSide::Left:
        OppositeSide = EBoxSide::Right;
        break;
    case EBoxSide::Right:
        OppositeSide = EBoxSide::Left;
        break;
    case EBoxSide::Top:
        OppositeSide = EBoxSide::Bottom;
        break;
    case EBoxSide::Bottom:
        OppositeSide = EBoxSide::Top;
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("Invalid box side requested for comparison!"));
        return false;
    }

    // Get the 2D array representation of the specified side for *this and the opposite side for Other
    TArray<TArray<bool>> ThisSide = GetBoxSide(Side);
    TArray<TArray<bool>> OtherOppositeSide = Other.GetBoxSide(OppositeSide);

    // Compare the two sides element by element
    if (ThisSide.Num() != OtherOppositeSide.Num() || ThisSide[0].Num() != OtherOppositeSide[0].Num())
    {
        return false; // Sides have different dimensions
    }

    for (int32 Y = 0; Y < ThisSide.Num(); ++Y)
    {
        for (int32 X = 0; X < ThisSide[0].Num(); ++X)
        {
            if (ThisSide[Y][X] != OtherOppositeSide[Y][X])
            {
                return false; // Found a difference
            }
        }
    }

    return true; // Sides are identical
}
