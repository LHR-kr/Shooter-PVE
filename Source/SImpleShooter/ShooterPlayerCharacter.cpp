// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerCharacter.h"
#include "Gun.h"
void AShooterPlayerCharacter::BeginPlay()
{   
    //부모 생성자에서 기본 총으로 라이플 생성
    Super::BeginPlay();

    //라이플 포인터에 저장.
    Rifle = Gun;

    RocketLauncher = SpawnNewGun(RocketLauncherClass);

    RocketLauncher->SetActorHiddenInGame(true);
    RocketLauncher->SetActorEnableCollision(false);
}


void AShooterPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&AShooterPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&AShooterPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUP"),this,&APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed, this,&ACharacter::Jump);
	//SetupPlayerInputComponent 함수가 Begin Play보다 먼저 호출된다. 그래서 Gun이 생성되기 전이므로 Gun의 함수를 바인딩 하는게 아니라, 이 클래스의 멤버 함수를 바인딩 해준다.
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this,&AShooterCharacter::Shoot);
    PlayerInputComponent->BindAction(TEXT("SwapWeapon1"), IE_Pressed, this,&AShooterPlayerCharacter::SwapToRifle);
    PlayerInputComponent->BindAction(TEXT("SwapWeapon2"), IE_Pressed, this,&AShooterPlayerCharacter::SwapToRocketLauncher);

}
void AShooterPlayerCharacter::MoveForward(float AxisValue)
{
	//AddMovementInput은 MovementCompnent의 영향 아래에 있다. 그래서 최대 속도 등도 Movement의 값을 벗어나지 못한다.
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterPlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}



void AShooterPlayerCharacter::SwapnWeapon(int index)
{
    
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
