// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineActor.h"

#include "InputBehavior.h"
#include "DynamicMesh/MeshTransforms.h"


// Sets default values
ASplineActor::ASplineActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");
	if(SplineComponent)
	{
		SetRootComponent(SplineComponent);  
	}  
}

// Called when the game starts or when spawned
void ASplineActor::BeginPlay()
{
	Super::BeginPlay();
	//UpdateMesh();
}

// Called every frame
void ASplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASplineActor::SpawnSplineMesh(UStaticMesh* StaticMesh, UMaterialInterface* Material, ESplineMeshAxis::Type ForwardAxis, FVector StartPoint, FVector StartTangent, FVector EndPoint, FVector EndTangent)
{
	USplineMeshComponent *SplineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
			
	// update mesh details
	SplineMesh->SetStartScale(Scale);
	SplineMesh->SetEndScale(Scale);
	SplineMesh->SetStaticMesh(StaticMesh);
	SplineMesh->SetForwardAxis(ForwardAxis, true);
	SplineMesh->SetMaterial(0, Material);
			
	
	// initialize the object
	SplineMesh->RegisterComponentWithWorld(GetWorld());
	
	SplineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;//?
	SplineMesh->SetMobility(EComponentMobility::Movable);
	
	SplineMesh->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	// define the positions of the points and tangents
	SplineMesh->SetStartAndEnd(StartPoint, StartTangent, EndPoint, EndTangent, true);
	
	// query physics
	SplineMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
}

void ASplineActor::UpdateMesh()
{
	
	if(SplineComponent && SplineMeshMap.Num() > 0)
	{

		FSplineMeshDetails* DefaultMeshDetails = nullptr;
		if(SplineMeshMap.Contains(ESplineMeshType::DEFAULT))
		{
			DefaultMeshDetails = SplineMeshMap.Find(ESplineMeshType::DEFAULT);	
		}
		else
		{
			// exit if we don't have a default mesh to work with
			return;
		}
		
		const int32 SplinePoints = SplineComponent->GetNumberOfSplinePoints();


		float SplinePartsSize = 0;
		if(SplinePartitionMethod==ESplinePartitionMethod::EVENLY)
		{
			const float Size = DefaultMeshDetails->size;
			if(Size!=0.0f)
				SplinePartsSize=((float)SplineComponent->GetSplineLength()/Size);
		}
		else if(SplinePartitionMethod==ESplinePartitionMethod::JOINTTOJOINT)
		{
			SplinePartsSize=SplinePoints-1;
		}

		Scale = FVector2d(DefaultMeshDetails->ScaleX,DefaultMeshDetails->ScaleY);
		
		for(int SplineCount = 0; SplineCount < SplinePartsSize; SplineCount++)
		{

			UStaticMesh* StaticMesh = DefaultMeshDetails->Mesh;
			UMaterialInterface* Material = nullptr;
			ESplineMeshAxis::Type ForwardAxis = DefaultMeshDetails->ForwardAxis;
			float Size = DefaultMeshDetails->size;
			// default assignment - middle mesh
			if(DefaultMeshDetails->DefaultMaterial)
			{
				Material = DefaultMeshDetails->DefaultMaterial;
			}			
			
			// define the positions of the points and tangents
			FVector StartPoint , StartTangent, EndPoint, EndTangent;

			if(SplinePartitionMethod==ESplinePartitionMethod::EVENLY)
			{
				
				StartPoint = SplineComponent->GetLocationAtDistanceAlongSpline(SplineCount*Size,ESplineCoordinateSpace::Type::Local);
				StartTangent = SplineComponent->GetTangentAtDistanceAlongSpline(SplineCount*Size,ESplineCoordinateSpace::Type::Local);
				EndPoint = SplineComponent->GetLocationAtDistanceAlongSpline((SplineCount+1)*(Size),ESplineCoordinateSpace::Type::Local);
				EndTangent = SplineComponent->GetTangentAtDistanceAlongSpline((SplineCount+1)*(Size),ESplineCoordinateSpace::Type::Local);
			}
			else if(SplinePartitionMethod==ESplinePartitionMethod::JOINTTOJOINT)
			{
				StartPoint = SplineComponent->GetLocationAtSplinePoint(SplineCount, ESplineCoordinateSpace::Type::Local);
				StartTangent = SplineComponent->GetTangentAtSplinePoint(SplineCount, ESplineCoordinateSpace::Type::Local);
				EndPoint = SplineComponent->GetLocationAtSplinePoint(SplineCount + 1, ESplineCoordinateSpace::Type::Local);
				EndTangent = SplineComponent->GetTangentAtSplinePoint(SplineCount + 1, ESplineCoordinateSpace::Type::Local);
			}

			SpawnSplineMesh(StaticMesh, Material, ForwardAxis, StartPoint, StartTangent, EndPoint, EndTangent);
		}
	}
}

void ASplineActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	//UpdateMesh();
	
}

USplineComponent* ASplineActor::GetSplineComponent() const
{
	return SplineComponent;
}

void ASplineActor::SetSplineComponent(USplineComponent* NewSplineComponent)
{
	if (NewSplineComponent)
	{
		SplineComponent = NewSplineComponent;
		SplineComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}
}
