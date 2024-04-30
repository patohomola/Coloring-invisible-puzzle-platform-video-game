
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildBlock.generated.h"
//#include "BuildBlock.h"

UCLASS()
class MYPROJECT_API ABuildBlock : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuildBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Mesh component for the block
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BlockMesh;

	// List of materials for the block
	UPROPERTY(EditAnywhere)
	TArray<class UMaterialInterface*> BlockMaterials;
	UPROPERTY(EditAnywhere)
	TArray<class UMaterialInterface*> BlockMaterialsInvincible;
	UPROPERTY(EditAnywhere)
	TArray<class UMaterialInterface*> BlockMaterialsCleanCanvas;

	// Method to initialize the block
	UFUNCTION(BlueprintCallable)
	void InitializeBlock();

	UFUNCTION(BlueprintCallable)
	void RandomRotateBlock();

private:
	// Method to select a random material from the list
	UMaterialInterface* GetRandomMaterial();
};
