// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

    HUDUI = CreateWidget(this, HUDUIClass);
    if(HUDUI !=nullptr)
    {
        HUDUI->AddToViewport();
    }

}
void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUDUI->RemoveFromViewport();
    if(bIsWinner)
    {
        //플레이어 컨틀롤러는 UI를 소유할 수 있다. 그래서 owner로 this를 인자로 넘겨준다.
        UUserWidget* WinScreenUI = CreateWidget(this, WinScreenUIClass);
        if(WinScreenUI !=nullptr)
        {
            WinScreenUI->AddToViewport();
        }
    }

    else
    {
        //플레이어 컨틀롤러는 UI를 소유할 수 있다.
        UUserWidget* LoseScreenUI = CreateWidget(this, LoseScreenUIClass);
        if(LoseScreenUI !=nullptr)
        {
            LoseScreenUI->AddToViewport();
        }
    }
    
    
    GetWorldTimerManager().SetTimer(RestartTimerHandle,this, &APlayerController::RestartLevel, RestartDelay);
}
