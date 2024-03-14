// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerIsSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "AIController.h"
UBTService_PlayerIsSeen::UBTService_PlayerIsSeen()
{
    NodeName = TEXT("Player Is Seen");
}

void UBTService_PlayerIsSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController * AIController = OwnerComp.GetAIOwner();
    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if(AIController == nullptr || Player == nullptr) return;
    
    if(AIController -> LineOfSightTo(Player))
    {
        AIController->GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),Player);
    }
    else
    {
         AIController->GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
