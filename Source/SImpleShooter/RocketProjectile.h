// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RocketProjectile.generated.h"



UCLASS()
class SIMPLESHOOTER_API ARocketProjectile : public AActor
{
	GENERATED_BODY()
	class UParitcleSystem;
public:	
	// Sets default values for this actor's properties
	ARocketProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UFUNCTION()    
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* ExplosionEffect;
	UPROPERTY(EditDefaultsOnly)
	class USoundBase* ExplosionSound;
	UPROPERTY(EditAnywhere)
	float ExplosionRadius;
	UPROPERTY(EditAnywhere)
	float Damage;
	
};
