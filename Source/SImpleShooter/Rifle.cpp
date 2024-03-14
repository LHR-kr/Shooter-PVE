// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

void ARifle::PullTrigger()
{
	Super::PullTrigger();

	FHitResult HitResult;
	FVector ShotDirection;

	APawn* GunOwner = GetOwnerPawn();
	if(GunOwner == nullptr) return;

	AController* EventInstigatorContoller = GetOwnerPawnController();
	if(EventInstigatorContoller == nullptr) return;

	bool bIsHitted = IsTraceHitted(HitResult, ShotDirection);
	if(bIsHitted)
	{ 
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitEffect,HitResult.ImpactPoint,ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),HitSound,HitResult.ImpactPoint);

		AActor* HitActor = HitResult.GetActor();
		if(HitActor)
		{
			UGameplayStatics::ApplyDamage(HitActor, Damage, GetOwner()->GetInstigatorController(),this,UDamageType::StaticClass());
		}

	}

}

bool ARifle::IsTraceHitted(FHitResult& OutHitResult, FVector& OutShootDirection)
{
	//out parameter
	FVector ViewLocation;
	FRotator ViewRotator;
	//카메라 뷰포트의 위치를 가져오고, 거기서 라인 트레이싱
	GetOwnerPawnController()->GetPlayerViewPoint(ViewLocation, ViewRotator);

	OutShootDirection = ViewRotator.Vector();
	FVector TraceStart = ViewLocation;
	//카메라의 회전을 고려하여 끝 벡터 계산
	FVector TraceEnd = TraceStart + OutShootDirection * MaxDistance;

	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());


	return GetWorld()->LineTraceSingleByChannel(OutHitResult,TraceStart,TraceEnd,TraceChannel, Params);
}