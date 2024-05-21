// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
//#include  "../RoomBuilder.h"
class ARoomBuilder;
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

#include "LevelExitTriggerBox.generated.h"

/**
 * 
 */



UCLASS()
class MYPROJECT_API ALevelExitTriggerBox : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ALevelExitTriggerBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool isActive=false;
	ARoomBuilder *RoomBuilder;
	// Declare the OnOverlapBegin function

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
	// Box component for the trigger box
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;
};
