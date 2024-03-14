// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,Mesh,TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound,Mesh,TEXT("MuzzleFlashSocket"));
}

void AGun::SetTraceChannel(ECollisionChannel NewTraceChannel)
{
	TraceChannel = NewTraceChannel;
}




APawn* AGun::GetOwnerPawn() const
{
	return Cast<APawn>(GetOwner());
}

AController* AGun::GetOwnerPawnController() const
{
	return GetOwnerPawn()->GetController();
}
