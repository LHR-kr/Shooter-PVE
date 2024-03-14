// Fill out your copyright notice in the Description page of Project Settings.


#include "AIShoterController.h"
#include "Kismet/GamePlayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AAIShoterController::BeginPlay()
{
    Super::BeginPlay();
    //BT 실행
    RunBehaviorTree(BehaviorTree);
    //블랙보드를 가져오고 값을 수정 
    GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    
}

void AAIShoterController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

bool AAIShoterController::IsDead()
{
    AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
    if(ControlledCharacter != nullptr)
    {
        return ControlledCharacter->GetIsDead();
    }
    return true;
}
