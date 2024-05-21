// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundPlatform.h"

// Sets default values
AGroundPlatform::AGroundPlatform()
{
	PlatformMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	//RootComponent = PlatformMesh;
	PlatformMesh->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	PlatformMesh->SetMobility(EComponentMobility::Movable);

}

void AGroundPlatform::InitializePlatform(FVector Scale)
{
	if(PlatformMesh)
		PlatformMesh->SetWorldScale3D(Scale);
}

void AGroundPlatform::SetVisible()
{
	if (PlatformMesh && Visible)
	{
		PlatformMesh->SetMaterial(0, Visible);
	}
}

void AGroundPlatform::SetInvisible()
{
	if (PlatformMesh && Invisible)
	{
		PlatformMesh->SetMaterial(0, Invisible);
	}
}


void AGroundPlatform::setMaterialByType(EMaterialSplat TypeOfMaterial)
{
	switch (TypeOfMaterial)
	{
	case EMaterialSplat::Visible:
		SetVisible();
		break;
	case EMaterialSplat::Invisible:
		SetInvisible();
		break;
	default:
		break;
	}	
}





