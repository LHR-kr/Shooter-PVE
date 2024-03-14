// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();


protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, Category="VisualEffect")
	UParticleSystem* MuzzleFlash; 
	UPROPERTY(EditDefaultsOnly, Category = "SoundEffect")
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere, Category="VisualEffect")
	UParticleSystem* HitEffect;
	UPROPERTY(EditDefaultsOnly, Category = "SoundEffect")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere)
	float MaxDistance = 1000.f;
	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	APawn* GetOwnerPawn() const;
	AController* GetOwnerPawnController() const;
	ECollisionChannel TraceChannel;
public:
	virtual void PullTrigger();
	UFUNCTION(BlueprintCallable)
	void SetTraceChannel(ECollisionChannel NewTraceChannel);
};
