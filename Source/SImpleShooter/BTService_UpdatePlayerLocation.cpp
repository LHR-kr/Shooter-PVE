// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GamePlayStatics.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
    NodeName = "Update Target Player";
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


    UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if(BlackBoard == nullptr || Player == nullptr) return;
    BlackBoard->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
    
}
