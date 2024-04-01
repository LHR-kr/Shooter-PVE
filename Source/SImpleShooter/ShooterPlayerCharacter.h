// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacter.h"
#include "InputActionValue.h"
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

	virtual void Shoot() override;
	AShooterPlayerCharacter();
private:
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void TurnRight(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);

	AGun* Rifle;
	AGun* RocketLauncher;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AGun> RocketLauncherClass;


	void SwapToRifle();

	void SwapToRocketLauncher();

	class UInputMappingContext* IMCOnField;
	class UInputAction* IAMoveForward;
	class UInputAction* IAMoveRight;
	class UInputAction* IALookUp;
	class UInputAction* IATurnRight;
	class UInputAction* IAShoot;
	class UInputAction* IAJump;
	class UInputAction* IASwapWeaponToRifle;
	class UInputAction* IASwapWeaponToRocketLauncher;

	void SetHideWeapon(AGun* HideGun, bool bHasHide);
	UInputAction* FindInputAction(FString Path);

};
