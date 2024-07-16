// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineGenerator.h"
#include <queue>  // For std::priority_queue
//#include <functional>  // For std::greater (optional, for min-heap)

// Define a custom structure for elements in the priority queue

void LogArray(const TArray<int32>& Array, const FString& ArrayName)
{
	FString OutputString = ArrayName + TEXT(": ");
	for (int32 Element : Array)
	{
		OutputString += FString::Printf(TEXT("%d "), Element);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OutputString);
}


template <typename InElementType>
struct TPriorityQueueNode {
	InElementType Element;
	float Koeficient;

	TPriorityQueueNode()
	{
	}

	TPriorityQueueNode(InElementType InElement, float InKoeficient)
	{
		Element = InElement;
		Koeficient = InKoeficient;
	}
	
	bool operator<(const TPriorityQueueNode<InElementType> Other) const
	{
		return Koeficient > Other.Koeficient;
	}
};
template <typename InElementType>
class TPriorityQueue {
public:
	TPriorityQueue()
	{
		Array.Heapify();
	}

public:
	// Always check if IsEmpty() before Pop-ing!
	InElementType Pop()
	{
		TPriorityQueueNode<InElementType> Node;
		Array.HeapPop(Node);
		return Node.Element;
	}

	TPriorityQueueNode<InElementType> Top()
	{
		return Array.HeapTop();
	}

	TPriorityQueueNode<InElementType> PopNode()
	{
		TPriorityQueueNode<InElementType> Node;
		Array.HeapPop(Node);
		return Node;
	}

	void Push(InElementType Element, float Koeficient)
	{
		Array.HeapPush(TPriorityQueueNode<InElementType>(Element, Koeficient));
	}

	bool IsEmpty() const
	{
		return Array.Num() == 0;
	}

	int32 Size()
	{
		return  Array.Num();
	}

private:
	TArray<TPriorityQueueNode<InElementType>> Array;
};


// Sets default values for this component's properties
USplineGenerator::USplineGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USplineGenerator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



// Called every frame
void USplineGenerator::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USplineGenerator::MakeSlowlyEleveated(USplineComponent* SplineComponent)
{
	// Adjust Z coordinate proportionally based on distance along the spline
	for (int32 i = 0; i < SplineComponent->GetNumberOfSplinePoints(); ++i)
	{
		float Distance = SplineComponent->GetDistanceAlongSplineAtSplinePoint(i);
		FVector Point = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		Point.Z = Distance *0.15f;  // Adjust Z proportionally
		SplineComponent->SetLocationAtSplinePoint(i, Point, ESplineCoordinateSpace::Local, false);
	}

	SplineComponent->UpdateSpline();
}

void USplineGenerator::CalculateTangents(USplineComponent* SplineComponent)
{
	// Calculate tangents
	for (int32 i = 1; i < SplineComponent->GetNumberOfSplinePoints() - 1; ++i)
	{
		FVector PreviousPoint = SplineComponent->GetLocationAtSplinePoint(i-1,ESplineCoordinateSpace::Local);
		FVector CurrentPoint = SplineComponent->GetLocationAtSplinePoint(i,ESplineCoordinateSpace::Local);
		FVector NextPoint = SplineComponent->GetLocationAtSplinePoint(i+1,ESplineCoordinateSpace::Local);

		FVector Dir = FVector(0,0,0);

		Dir += (PreviousPoint-CurrentPoint).GetSafeNormal();
		Dir -=  (NextPoint-CurrentPoint).GetSafeNormal();
		Dir = Dir.GetSafeNormal();
		// Calculate the distance for the control points
		float DistanceToPrev = FVector::Dist(PreviousPoint, CurrentPoint);
		float DistanceToNext = FVector::Dist(CurrentPoint, NextPoint);

		FVector ArriveTangent = Dir * DistanceToPrev * -1.f;
		FVector LeaveTangent = Dir * DistanceToNext * -1.f;

		

		SplineComponent->SetTangentsAtSplinePoint(i, ArriveTangent, LeaveTangent, ESplineCoordinateSpace::Local);
	}

	

	

	// Set tangents for the first and last points
	if (SplineComponent->GetNumberOfSplinePoints() > 1)
	{
		FVector FirstPoint = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local);
		FVector SecondPoint = SplineComponent->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::Local);
		FVector FirstTangent = (SecondPoint - FirstPoint) / 2.0f;
		SplineComponent->SetTangentsAtSplinePoint(0, FirstTangent, FirstTangent, ESplineCoordinateSpace::Local);

		int32 LastIndex = SplineComponent->GetNumberOfSplinePoints() - 1;
		FVector LastPoint = SplineComponent->GetLocationAtSplinePoint(LastIndex, ESplineCoordinateSpace::Local);
		FVector SecondLastPoint = SplineComponent->GetLocationAtSplinePoint(LastIndex - 1, ESplineCoordinateSpace::Local);
		FVector LastTangent = (LastPoint - SecondLastPoint) / 2.0f;
		SplineComponent->SetTangentsAtSplinePoint(LastIndex, LastTangent, LastTangent, ESplineCoordinateSpace::Local);
	}

	SplineComponent->UpdateSpline();
}

void USplineGenerator::GenerateRandomTangle( int32 NumberOfPoints,float minDist, float Start, float Exit)
{
	USplineComponent* SplineComponent = SplineActor->GetSplineComponent();
	SplineComponent->ClearSplinePoints(false);

	TArray<FVector> Points;
		
	
	// Generate random points within bounds
	FVector lastpoint= FVector(Start,-Area.Y,0.f);
	Points.Add(lastpoint - FVector(0,10,0));
	FVector newPoint = lastpoint;
	for (int32 i = 0; i < NumberOfPoints; ++i)
	{
		Points.Add(newPoint);
		while (FVector::Dist(lastpoint,newPoint)<minDist)
		{
			newPoint =GetRandomPointWithinBounds(Area.X, Area.Y);
	 	}
		
		lastpoint=newPoint;
	}
	Points.Add(newPoint);
	Points.Add(FVector(Exit,Area.Y,0.f));
	Points.Add(FVector(Exit,Area.Y+10,0.f));

	// Add points to the spline
	for (int32 i = 0; i < Points.Num(); ++i)
	{
		SplineComponent->AddSplinePoint(Points[i], ESplineCoordinateSpace::Local, false);
		
	}
	
	
	CalculateTangents(SplineComponent);

	//Subdivide the mesh for destroying s InterSection
	//SplineActor->UpdateMesh();

	SubdivideSpline(SplineComponent);
	SubdivideSpline(SplineComponent);

	CalculateTangents(SplineComponent);
	Diameter = 500.f;
	
	TArray<int32> IntersectionIndicesDown;
	TArray<int32> IntersectionIndicesUp;

	int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
	int32 LastIntersectionIndex = 0;

	for (int32 i = 2; i < NumPoints - 1; ++i)
	{
		for (int32 j = LastIntersectionIndex; j < i - 2; ++j)
		{
			if (CalculateShortestDistanceBetweenSplineSegments(i,j,SplineComponent)<Diameter)
			{
				IntersectionIndicesDown.Add(j);
				IntersectionIndicesUp.Add(i);
				LastIntersectionIndex = j+1; // Update the last intersection index
				break; // Stop checking further segments for this point
			}
		}
	}
	
	


	float value = 0.f;
	float previousDist = 0.f;
	TPriorityQueue<int32> Frontier;
	
	Frontier.Push(NumPoints,value);
	int32 intGetIndex = 0;

	UE_LOG(LogTemp, Warning, TEXT("INtersections = %d"), IntersectionIndicesDown.Num());
	UE_LOG(LogTemp, Warning, TEXT("co= %d"), NumPoints);

	LogArray(IntersectionIndicesDown,"Down");
	LogArray(IntersectionIndicesUp,"UP__");
	for (int32 i = 0; i < NumPoints; ++i)
	{
		float Distance = SplineComponent->GetDistanceAlongSplineAtSplinePoint(i);
		float Koeficient = Frontier.Top().Koeficient;
		value += (Distance-previousDist)*Koeficient;
		previousDist=Distance;

		if(intGetIndex<IntersectionIndicesDown.Num())
		{
			if(IntersectionIndicesDown[intGetIndex]==i)
			{
				int Element = IntersectionIndicesUp[intGetIndex];
				float EndDistance = SplineComponent->GetDistanceAlongSplineAtSplinePoint(Element);
				float delta = EndDistance-Distance;
				float koeficient2 = Diameter/delta;
				Frontier.Push(Element,koeficient2);
				intGetIndex++;
				UE_LOG(LogTemp, Warning, TEXT("FrontierSize= %d"), Frontier.Size());
			}
		}

		while (!Frontier.IsEmpty() && Frontier.Top().Element<i){
			Frontier.Pop();
		}
		
		FVector Point = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		Point.Z = value;  // Adjust Z proportionally
		SplineComponent->SetLocationAtSplinePoint(i, Point, ESplineCoordinateSpace::Local, false);
	}

	SplineComponent->UpdateSpline();

	//MakeSlowlyEleveated(SplineComponent);	

}


FVector USplineGenerator::GetRandomPointWithinBounds(float AreaSizeX,float AreaSizeY) const
{
	return FVector(
		FMath::FRandRange(-AreaSizeX, AreaSizeX),
		FMath::FRandRange(-AreaSizeY, AreaSizeY),
		0.0f
	);
}

void USplineGenerator::SubdivideSpline(USplineComponent* SplineComponent)
{
	int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
	TArray<FVector> NewPoints;

	for (int32 i = 0; i < NumPoints - 1; i++)
	{
		FVector Start = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		FVector End = SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
		float StartDistance = SplineComponent->GetDistanceAlongSplineAtSplinePoint(i);
		float EndDistance = SplineComponent->GetDistanceAlongSplineAtSplinePoint(i + 1);
		if(EndDistance-StartDistance>Diameter*2.f)
		{
			float MidDistance = (StartDistance + EndDistance) / 2.0f;

			FVector MidPoint = SplineComponent->GetLocationAtDistanceAlongSpline(MidDistance, ESplineCoordinateSpace::Local);
			NewPoints.Add(Start);
			NewPoints.Add(MidPoint);
		}
		else
		{
			NewPoints.Add(Start);
		}
	}
	NewPoints.Add(SplineComponent->GetLocationAtSplinePoint(NumPoints - 1, ESplineCoordinateSpace::Local));

	SplineComponent->ClearSplinePoints(false);

	for (int32 i = 0; i < NewPoints.Num(); i++)
	{
		SplineComponent->AddSplinePoint(NewPoints[i], ESplineCoordinateSpace::Local, false);
	}
	SplineComponent->UpdateSpline();
}

float GetSegmentSegmentDistance2d(const FVector& P1, const FVector& P2, const FVector& Q1, const FVector& Q2)
{
	FVector Intersection=FVector::Zero();
	if(FMath::SegmentIntersection2D(P1,P2,Q1,Q2,Intersection ))
		return 0.0f;
	//segment does not intersect intesect
	float a=FMath::PointDistToSegment(P1, Q1, Q2);
	float b=FMath::PointDistToSegment(P2, Q1, Q2);
	float c=FMath::PointDistToSegment(Q1, P1, P1);
	float d=FMath::PointDistToSegment(Q2, P1, P2);
	

	float delta =  FMath::Min(FMath::Min(a,b),FMath::Min(c,d));
	return delta;
	
}

float GetSegmentSegmentDistance(const FVector& P1, const FVector& P2, const FVector& Q1, const FVector& Q2)
{
	FVector d1 = P2 - P1;
	FVector d2 = Q2 - Q1;
	FVector r = P1 - Q1;
	float a = FVector::DotProduct(d1, d1);
	float e = FVector::DotProduct(d2, d2);
	float f = FVector::DotProduct(d2, r);

	float s = 0.0f;
	float t = 0.0f;

	if (a <= KINDA_SMALL_NUMBER && e <= KINDA_SMALL_NUMBER) 
	{
		// Both segments degenerate into points
		return FVector::Dist(P1, Q1);
	}
	if (a <= KINDA_SMALL_NUMBER) 
	{
		// First segment degenerates into a point
		s = 0.0f;
		t = FMath::Clamp(f / e, 0.0f, 1.0f);
	}
	else 
	{
		float c = FVector::DotProduct(d1, r);
		if (e <= KINDA_SMALL_NUMBER) 
		{
			// Second segment degenerates into a point
			t = 0.0f;
			s = FMath::Clamp(-c / a, 0.0f, 1.0f);
		}
		else 
		{
			// The general non-degenerate case starts here
			float b = FVector::DotProduct(d1, d2);
			float denom = a * e - b * b;

			if (denom != 0.0f) 
			{
				s = FMath::Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
			}
			else 
			{
				s = 0.0f;
			}

			t = (b * s + f) / e;

			if (t < 0.0f) 
			{
				t = 0.0f;
				s = FMath::Clamp(-c / a, 0.0f, 1.0f);
			}
			else if (t > 1.0f) 
			{
				t = 1.0f;
				s = FMath::Clamp((b - c) / a, 0.0f, 1.0f);
			}
		}
	}

	FVector closestPointOnP = P1 + s * d1;
	FVector closestPointOnQ = Q1 + t * d2;
	return FVector::Dist(closestPointOnP, closestPointOnQ);
}

float USplineGenerator::CalculateShortestDistanceBetweenSplineSegments(int32 SegmentIndex1, int32 SegmentIndex2,USplineComponent* SplineComponent) const
{
	if (SplineComponent->GetNumberOfSplinePoints() > SegmentIndex1 + 1 && SplineComponent->GetNumberOfSplinePoints() > SegmentIndex2 + 1)
	{
		FVector Start1 = SplineComponent->GetLocationAtSplinePoint(SegmentIndex1, ESplineCoordinateSpace::World);
		FVector End1 = SplineComponent->GetLocationAtSplinePoint(SegmentIndex1 + 1, ESplineCoordinateSpace::World);
		FVector Start2 = SplineComponent->GetLocationAtSplinePoint(SegmentIndex2, ESplineCoordinateSpace::World);
		FVector End2 = SplineComponent->GetLocationAtSplinePoint(SegmentIndex2 + 1, ESplineCoordinateSpace::World);
		
		float delta = GetSegmentSegmentDistance2d(Start1,End1,Start2,End2);

		
 		return delta;
	}

	return 0.0f;
}
