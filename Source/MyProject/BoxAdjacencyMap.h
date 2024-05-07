#pragma once

#include "CoreMinimal.h"
#include "Box.h"
#include "Containers/Map.h"
#include "Containers/Set.h"

class MYPROJECT_API BoxAdjacencyMap
{
public:
	// Constructor
	BoxAdjacencyMap();

	// Method to populate the adjacency map with provided box components
	void BuildAdjacencyMap(const TArray<BoxComponent>& BoxComponents);

	// Method to get adjacent box components for a given box component and side
	const TArray<BoxComponent>* GetAdjacentBoxes(const BoxComponent& Box, EBoxSide Side) const;

private:
	// Map to store adjacency relationships
	TMap<BoxComponent, TMap<EBoxSide, TArray<BoxComponent>>> AdjacencyMap;

	// Helper function to determine if two box sides match
	bool DoSidesMatch(const TArray<TArray<bool>>& Side1, const TArray<TArray<bool>>& Side2) const;
};

/*
*BoxAdjacencyMap AdjacencyMap;
AdjacencyMap.BuildAdjacencyMap(MyArrayOfBoxComponents);

// Get adjacent boxes for a specific box and side
const TArray<BoxComponent>* AdjacentBoxes = AdjacencyMap.GetAdjacentBoxes(MyBoxComponent, EBoxSide::Front);
if (AdjacentBoxes)
{
// Process the list of adjacent boxes
for (const BoxComponent& AdjacentBox : *AdjacentBoxes)
{
// Do something with the adjacent box
}
}
*/
