// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketLanucher.h"
#include "RocketProjectile.h"
#include "TimerManager.h"



void ARocketLanucher::PullTrigger()
{
    if(!bCanLaunch) return;
    SetLaunchEnable(false);

    Super::PullTrigger();

    FVector ViewpointLocation;
    FRotator ViewpointRotator;
    GetOwnerPawnController()->GetPlayerViewPoint(ViewpointLocation, ViewpointRotator);

    AActor* Projectile = GetWorld()->SpawnActor<AActor>(
        RocketProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ViewpointRotator);
    Projectile->SetOwner(GetOwner());


    FTimerDelegate SetLaunchEnableTimeDelegate = FTimerDelegate::CreateUObject(this, &ARocketLanucher::SetLaunchEnable,true);
    GetWorldTimerManager().SetTimer(LaunchTimerHandle,SetLaunchEnableTimeDelegate,LaunchDelay, false);
}

ARocketLanucher::ARocketLanucher()
{
    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(Mesh);

}

void ARocketLanucher::SetLaunchEnable(bool bValue)
{
    bCanLaunch = bValue;
}

