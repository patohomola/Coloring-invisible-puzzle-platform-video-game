// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject/Components/OutputSenderComponent.h"
#include "AInputControllerActor.generated.h"


UCLASS()
class MYPROJECT_API AInputControllerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AInputControllerActor();

	void AsignDelegateToEvent(UOutputSenderComponent* OutputSender,TFunction<void(bool)> AsignFunction);

protected:
	virtual void BeginPlay() override;

public:
	// References to the spawned objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> Sender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> ReceiverActor;
};