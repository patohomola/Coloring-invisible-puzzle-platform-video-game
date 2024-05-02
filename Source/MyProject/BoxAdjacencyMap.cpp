#include "BoxAdjacencyMap.h"
#include "BoxAdjacencyMap.h"

BoxAdjacencyMap::BoxAdjacencyMap()
{
    // Constructor
}

void BoxAdjacencyMap::BuildAdjacencyMap(const TArray<BoxComponent>& BoxComponents)
{
    // Clear the existing map
    AdjacencyMap.Empty();

    // Iterate through each box component
    for (const BoxComponent& Box : BoxComponents)
    {
        // Initialize a map to store adjacent boxes per side
        TMap<EBoxSide, TArray<BoxComponent>> AdjacentBoxesPerSide;

        // Iterate over each box's side to find matches with other boxes
        for (int32 i = 0; i < static_cast<int32>(EBoxSide::Bottom); ++i) // Loop over all sides
        {
            EBoxSide Side = static_cast<EBoxSide>(i);

            // Find adjacent boxes that share this side
            TArray<BoxComponent> AdjacentBoxes;

            for (const BoxComponent& OtherBox : BoxComponents)
            {
                if (&OtherBox != &Box) // Skip comparing with itself
                {
                    if (Box.CompareSide(OtherBox, Side))
                    {
                        AdjacentBoxes.Add(OtherBox);
                    }
                }
            }

            // Add to the adjacency map
            AdjacentBoxesPerSide.Add(Side, AdjacentBoxes);
        }

        // Add to the main adjacency map
        AdjacencyMap.Add(Box, AdjacentBoxesPerSide);
    }
}

const TArray<BoxComponent>* BoxAdjacencyMap::GetAdjacentBoxes(const BoxComponent& Box, EBoxSide Side) const
{
    const TMap<EBoxSide, TArray<BoxComponent>>* AdjacentBoxesPerSide = AdjacencyMap.Find(Box);
    if (AdjacentBoxesPerSide)
    {
        const TArray<BoxComponent>* AdjacentBoxes = AdjacentBoxesPerSide->Find(Side);
        return AdjacentBoxes;
    }

    return nullptr;
}

bool BoxAdjacencyMap::DoSidesMatch(const TArray<TArray<bool>>& Side1, const TArray<TArray<bool>>& Side2) const
{
    // Implement logic to compare two sides of boxes
    // You would need to define how two sides match (e.g., identical boolean array comparison)
    // This depends on your specific implementation requirements.
    return false; // Placeholder logic
}
