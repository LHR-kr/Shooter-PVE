// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerCharacter.h"
#include "Gun.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AShooterPlayerCharacter::AShooterPlayerCharacter()
{
    IAMoveForward = FindInputAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_MoveForward.IA_MoveForward'"));
    IAMoveRight = FindInputAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_MoveRight.IA_MoveRight'"));
    IALookUp = FindInputAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_LookUP.IA_LookUP'"));
	IATurnRight = FindInputAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_TurnRIght.IA_TurnRIght'"));
	IAShoot = FindInputAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Shoot.IA_Shoot'"));
	IAJump = FindInputAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Jump.IA_Jump'"));
	IASwapWeaponToRifle = FindInputAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_SwapWeaponToRifle.IA_SwapWeaponToRifle'"));
	IASwapWeaponToRocketLauncher = FindInputAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_SwapWeaponToRocketLauncher.IA_SwapWeaponToRocketLauncher'"));
} 

void AShooterPlayerCharacter::BeginPlay()
{    
    //부모 생성자에서 기본 총으로 라이플 생성
    Super::BeginPlay();

    //라이플 포인터에 저장.
    Rifle = Gun;

    RocketLauncher = SpawnNewGun(RocketLauncherClass);

    RocketLauncher->SetActorHiddenInGame(true);
    RocketLauncher->SetActorEnableCollision(false);

    if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if(UEnhancedInputLocalPlayerSubsystem* Subsystem = 
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController -> GetLocalPlayer()))
        Subsystem->AddMappingContext(IMCOnField,0);
    }
}


void AShooterPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(IAMoveForward,ETriggerEvent::Triggered, this, &AShooterPlayerCharacter::MoveForward);
        EnhancedInputComponent->BindAction(IAMoveRight,ETriggerEvent::Triggered, this, &AShooterPlayerCharacter::MoveRight);
        EnhancedInputComponent->BindAction(IALookUp,ETriggerEvent::Triggered, this, & AShooterPlayerCharacter::LookUp);
        EnhancedInputComponent->BindAction(IATurnRight,ETriggerEvent::Triggered, this, &AShooterPlayerCharacter::TurnRight);
        //SetupPlayerInputComponent 함수가 Begin Play보다 먼저 호출된다. 그래서 Gun이 생성되기 전이므로 Gun의 함수를 바인딩 하는게 아니라, 이 클래스의 멤버 함수를 바인딩 해준다.
        EnhancedInputComponent->BindAction(IAShoot,ETriggerEvent::Started, this, &AShooterCharacter::Shoot);
        EnhancedInputComponent->BindAction(IAJump,ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(IASwapWeaponToRifle,ETriggerEvent::Started, this, &AShooterPlayerCharacter::SwapToRifle);
        EnhancedInputComponent->BindAction(IASwapWeaponToRocketLauncher,ETriggerEvent::Started, this, &AShooterPlayerCharacter::SwapToRocketLauncher);

    }
}

void AShooterPlayerCharacter::Shoot()
{
    Super::Shoot();
}




void AShooterPlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	//AddMovementInput은 MovementCompnent의 영향 아래에 있다. 그래서 최대 속도 등도 Movement의 값을 벗어나지 못한다.
	AddMovementInput(GetActorForwardVector() * Value.Get<float>());
}

void AShooterPlayerCharacter::MoveRight(const FInputActionValue& Value)
{
	AddMovementInput(GetActorRightVector() *  Value.Get<float>());
}

void AShooterPlayerCharacter::TurnRight(const FInputActionValue& Value)
{
    APawn::AddControllerYawInput(Value.Get<float>());
}

void AShooterPlayerCharacter::LookUp(const FInputActionValue& Value)
{
    APawn::AddControllerPitchInput(Value.Get<float>());
}


void AShooterPlayerCharacter::SwapToRifle()
{
    if(Gun == nullptr || Rifle == nullptr) return;
    if(Gun == Rifle) return;

    SetHideWeapon(RocketLauncher,true);
    SetHideWeapon(Rifle,false);
    Gun=Rifle;
}

void AShooterPlayerCharacter::SwapToRocketLauncher()
{
    if(Gun == nullptr || RocketLauncher == nullptr) return;
    if(Gun == RocketLauncher) return;

    SetHideWeapon(Rifle,true);
    SetHideWeapon(RocketLauncher,false);
    Gun=RocketLauncher;
}

void AShooterPlayerCharacter::SetHideWeapon(AGun* HideGun, bool bHasHide)
{
    HideGun->SetActorHiddenInGame(bHasHide);
    HideGun->SetActorEnableCollision(!bHasHide);
}

UInputAction* AShooterPlayerCharacter::FindInputAction(FString Path)
{
	ConstructorHelpers::FObjectFinder<UInputAction>MyAsset((TEXT("%s"), *Path));
    return MyAsset.Object;
}

