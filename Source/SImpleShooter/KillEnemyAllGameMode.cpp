// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEnemyAllGameMode.h"
#include "EngineUtils.h"
#include "AIShoterController.h"

void AKillEnemyAllGameMode::KillPawn(APawn* PawnKilled)
{
    Super::KillPawn(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController != nullptr)
    {
        EndGame(false);
    }

    for(AAIShoterController* AIController : TActorRange<AAIShoterController>(GetWorld()))
    {
        if(!AIController -> IsDead()) return;
    }

    EndGame(true);
}

void AKillEnemyAllGameMode::EndGame(bool bIsPlayerWinner)
{
    //EngineUtils.h 
    //TActorRange로 월드 내의 AController를 가지는 모든 객체의 래인지 반환.
    for(AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWin = bIsPlayerWinner == Controller ->IsPlayerController();
        Controller->GameHasEnded(Controller->GetPawn(), bIsWin);
    }
}
