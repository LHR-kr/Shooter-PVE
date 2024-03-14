// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//Apply Damage에서 TakeDamage 호출한다.
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool GetIsDead()const;
	void Shoot();
	UFUNCTION(BlueprintPure)
	float GetHPPercent()const;
private:

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxHP = 100.0f;
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	float HP;
	bool IsDead = false;


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AGun> RifleClass;
	UPROPERTY()
	AGun* Gun;
	AGun* SpawnNewGun(UClass* GunClass);
};
