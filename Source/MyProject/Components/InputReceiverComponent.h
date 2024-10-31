// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputReceiverComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnOnDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnOffDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT_API UInputReceiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInputReceiverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void TurnSelfOn();

	UFUNCTION(BlueprintCallable)
	void TurnSelfOff();

	UFUNCTION(BlueprintCallable)
	bool ToggleSelf();

	UFUNCTION(BlueprintCallable)
	bool GetSelfState() const;

private:
	// Component state variable
	UPROPERTY(EditAnywhere)
	bool MyState;

public:
	UPROPERTY(BlueprintAssignable, Category = "InputReceiver")
	FOnTurnOnDelegate OnTurnOn;
	UPROPERTY(BlueprintAssignable, Category = "InputReceiver")
	FOnTurnOffDelegate OnTurnOff;
};
