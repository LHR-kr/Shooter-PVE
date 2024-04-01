// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "SImpleShooterGameModeBase.h"
#include "ShooterPlayerController.h"
#include "Containers/EnumAsByte.h"
#include "Rifle.h"
// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//원래 메시에 있던 총 메시 가리기
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	
	Gun = SpawnNewGun(RifleClass);

	if(Cast<AShooterPlayerController>(GetController()))
		Gun->SetTraceChannel(ECollisionChannel::ECC_GameTraceChannel3); // bullet for enemy channel
	else
		Gun->SetTraceChannel(ECollisionChannel::ECC_GameTraceChannel2); // bullet for player channel
	HP = MaxHP;
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent,EventInstigator, DamageCauser);

	DamageApplied = FMath::Min(HP, DamageApplied);

	if(GetIsDead()) return 0.f;

	HP-=DamageApplied;
	if(HP <=0 )
	{
		IsDead = true;
		ASImpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASImpleShooterGameModeBase>();
		if(GameMode != nullptr)
		{
			GameMode->KillPawn(this);
		}
		DetachFromControllerPendingDestroy();
		SetActorEnableCollision(false);
	}
	return DamageApplied;
}

bool AShooterCharacter::GetIsDead() const
{
	return IsDead;
}



void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}

float AShooterCharacter::GetHPPercent() const
{
	return HP/MaxHP;
}

AGun* AShooterCharacter::SpawnNewGun(UClass* GunClass)
{
	AGun* NewGun = GetWorld()->SpawnActor<AGun>(GunClass);
	//AActor::AttachToComponent(), 해당 액터의 루트 컴포넌트를 인자로 받은 USceneComponent의 자식으로 만든다.
	NewGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	//나중에 데미지 처리를 위해 캐릭터를 건의 owner로 지정한다.
	NewGun->SetOwner(this);
	return NewGun;
}

