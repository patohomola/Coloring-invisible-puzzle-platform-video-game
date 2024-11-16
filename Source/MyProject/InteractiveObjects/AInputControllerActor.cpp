// Fill out your copyright notice in the Description page of Project Settings.


#include "AInputControllerActor.h"
#include  "../Components/InputReceiverComponent.h"
#include "Kismet/GameplayStatics.h"

AInputControllerActor::AInputControllerActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInputControllerActor::BeginPlay()
{
	Super::BeginPlay();

	// Spawn ObjectA and ObjectB in the worl
	AActor* ActorObjectA = GetWorld()->SpawnActor<AActor>(Sender, GetActorLocation(), FRotator::ZeroRotator);

	AActor* ActorObjectB = GetWorld()->SpawnActor<AActor>(ReceiverActor, GetActorLocation() + FVector(100, 0, 0), FRotator::ZeroRotator);

	AActor* ActorObjectC = GetWorld()->SpawnActor<AActor>(ReceiverActor, GetActorLocation() + FVector(500, 0, 0), FRotator::ZeroRotator);
	
	// Add the components to ObjectA and ObjectB
	UOutputSenderComponent* OutputSender = ActorObjectA->FindComponentByClass<UOutputSenderComponent>();
	//OutputSender->RegisterComponent();

	UInputReceiverComponent* InputReceiver = ActorObjectB->FindComponentByClass<UInputReceiverComponent>();
	//InputReceiver->RegisterComponent();

	UInputReceiverComponent* InputReceiverC = ActorObjectC->FindComponentByClass<UInputReceiverComponent>();
	//InputReceiver->RegisterComponent();

	// Bind ObjectB's InputReceiver to respond to ObjectA's OutputSender
	if (OutputSender && InputReceiver)
	{
		//OutputSender->OnStateChanged.AddDynamic(InputReceiver, &UInputReceiverComponent::ToggleSelf);
		AsignDelegateToEvent(OutputSender,[InputReceiver,InputReceiverC](bool IsTurnedOn)
		{
			
			//InputReceiver->ToggleSelf();
			InputReceiver->TurnSelfOn();
			InputReceiverC->TurnSelfOn();
		});
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Or Output Is Wrong Defined"));
	}

	// Trigger ObjectA's state change to see ObjectB's reaction
	
}

void AInputControllerActor::AsignDelegateToEvent(UOutputSenderComponent* OutputSender, TFunction<void(bool)> AsignFunction)
{
	OutputSender->OnStateChangeScript.BindLambda(AsignFunction);
}
