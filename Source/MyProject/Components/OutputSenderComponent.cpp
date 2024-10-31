// Fill out your copyright notice in the Description page of Project Settings.


#include "OutputSenderComponent.h"


// Sets default values for this component's properties
UOutputSenderComponent::UOutputSenderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOutputSenderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOutputSenderComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


bool UOutputSenderComponent::GetState()
{
	return MyState;
}

void UOutputSenderComponent::ChangeThisObjectsState()
{
	MyState=!MyState;
	OnStateChanged.Broadcast(MyState);
}

