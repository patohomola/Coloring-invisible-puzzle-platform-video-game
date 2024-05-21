// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GroundPlatform.generated.h"


UENUM(BlueprintType)
enum class EMaterialSplat : uint8
{
	Visible UMETA(DisplayName = "Visible"),
	Invisible UMETA(DisplayName = "Invisible"),
};


UCLASS()

class MYPROJECT_API AGroundPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroundPlatform();
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* Visible;
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* Invisible;

	void SetVisible();
	void SetInvisible();
	void setMaterialByType(EMaterialSplat TypeOfMaterial);
protected:


public:
	UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* PlatformMesh;

	void InitializePlatform(FVector Scale);

};
