// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OutputSenderComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChange, const bool, IsTurnedOn);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT_API UOutputSenderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOutputSenderComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Dispatcher")
	void ChangeThisObjectsState();

	UFUNCTION(BlueprintCallable)
	bool GetState();
private:
	// Component state variable
	UPROPERTY(EditAnywhere)
	bool MyState;

public:
	UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	FOnStateChange OnStateChanged;

};
