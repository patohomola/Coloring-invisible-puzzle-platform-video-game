// Fill out your copyright notice in the Description page of Project Settings.


#include "InputReceiverComponent.h"


// Sets default values for this component's properties
UInputReceiverComponent::UInputReceiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInputReceiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInputReceiverComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInputReceiverComponent::TurnSelfOn()
{
	MyState = true;
	OnTurnOn.Broadcast();
}

void UInputReceiverComponent::TurnSelfOff()
{
	MyState = false;
	
	OnTurnOff.Broadcast();
}

bool UInputReceiverComponent::ToggleSelf()
{
	MyState = !MyState;
	if (MyState)
	{
		TurnSelfOn();
	}
	else
	{
		TurnSelfOff();
	}
	return MyState;
}

bool UInputReceiverComponent::GetSelfState() const
{
	return MyState;
}

