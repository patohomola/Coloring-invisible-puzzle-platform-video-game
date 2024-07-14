// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameFramework/Actor.h"

#include "Engine/DataTable.h"

#include "SplineActor.generated.h"


UENUM(BlueprintType)
enum class ESplineMeshType: uint8 {
	DEFAULT		UMETA(DisplayName = "Default Mesh"),
	START		UMETA(DisplayName = "Starting Mesh"),
	END			UMETA(DisplayName = "EndingMesh"),
};

USTRUCT(BlueprintType)
struct FSplineMeshDetails : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ScaleX;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ScaleY;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float size;

	FSplineMeshDetails() : ForwardAxis(ESplineMeshAxis::Type::X)
	{
	}
};

UENUM()
enum ESplinePartitionMethod
{
	JOINTTOJOINT UMETA(DisplayName = "Joint To Joint"),
	EVENLY UMETA(DisplayName = "Evenly"),
};

UCLASS()
class MYPROJECT_API ASplineActor : public AActor
{
	GENERATED_BODY()
public:

	
	UPROPERTY(VisibleAnywhere, Category = "OrganicLine")
	USplineComponent* SplineComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "OrganicLine")
	TMap<ESplineMeshType, FSplineMeshDetails> SplineMeshMap;

	UPROPERTY(EditAnywhere, Category = "OrganicLine")
	TEnumAsByte<ESplinePartitionMethod> SplinePartitionMethod;
	
	virtual void OnConstruction(const FTransform& Transform) override;
	
	USplineComponent* GetSplineComponent() const;
	void SetSplineComponent(USplineComponent* NewSplineComponent);
	// Sets default values for this actor's properties
	ASplineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	FVector2d Scale;
public:
	// Called every frame
	
	virtual void Tick(float DeltaTime) override;
	void SpawnSplineMesh(UStaticMesh* StaticMesh, UMaterialInterface* Material, ESplineMeshAxis::Type ForwardAxis,
	                     FVector StartPoint, FVector StartTangent, FVector EndPoint, FVector EndTangent);
	void UpdateMesh();
};
