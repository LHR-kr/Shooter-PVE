// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacter.h"
#include "ShooterPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerCharacter : public AShooterCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	AGun* Rifle;
	AGun* RocketLauncher;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AGun> RocketLauncherClass;

	void SwapnWeapon(int index);
	void SwapToRifle();
	void SwapToRocketLauncher();

	void SetHideWeapon(AGun* HideGun, bool bHasHide);
};
