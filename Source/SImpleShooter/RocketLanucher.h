// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "RocketLanucher.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ARocketLanucher : public AGun
{
	GENERATED_BODY()
public:
	virtual void PullTrigger() override;
	ARocketLanucher();

	void SetLaunchEnable(bool bValue);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ARocketProjectile> RocketProjectileClass;

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	float LaunchDelay = 0.f;
	bool bCanLaunch = true;
	struct FTimerHandle LaunchTimerHandle;

	
};
