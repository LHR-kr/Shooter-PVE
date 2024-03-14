// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h"

// Sets default values
ARocketProjectile::ARocketProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//메시를 루트로 해 놓아야 충돌이 루트에서 충돌이 감지 된다.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);


	//액터 컴포넌트이므로 계층 설정하지 못한다.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

}

// Called when the game starts or when spawned
void ARocketProjectile::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &ARocketProjectile::OnHit);
}

// Called every frame
void ARocketProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARocketProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, Hit.ImpactPoint, GetActorRotation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ExplosionSound, Hit.ImpactPoint);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(GetOwner());


	UGameplayStatics::ApplyRadialDamage(GetWorld(),Damage,Hit.ImpactPoint,ExplosionRadius,UDamageType::StaticClass(), IgnoreActors , this, GetOwner()->GetInstigatorController(),true, ECollisionChannel::ECC_GameTraceChannel2);
	//DrawDebugSphere(GetWorld(), Hit.ImpactPoint,ExplosionRadius, 32, FColor::Red, false, 5,0, 3);
	
	Destroy();
}

