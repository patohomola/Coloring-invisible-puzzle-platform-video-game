// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelExitTriggerBox.h"
#include "../RoomBuilder.h"
#include "GameFramework/Character.h"

// Sets default values
ALevelExitTriggerBox::ALevelExitTriggerBox()
{
	// Initialize the box component and set its size
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	//TriggerBox->InitBoxExtent(FVector(100.f, 100.f, 100.f));
	//TriggerBox->SetCollisionProfileName("Trigger");
	RootComponent = TriggerBox;

	// Bind the overlap event
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelExitTriggerBox::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ALevelExitTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelExitTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool odd = true;
void ALevelExitTriggerBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (OtherActor && Character && isActive)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NewRoom!"));	
		isActive=false;
		odd=!odd;
		if(odd==false)
		{
			RoomBuilder->CreateRandomRoom();
		}else
		{
			isActive=true;
		}
		
		//Todo: Make time increase based on curent time level
	}
}