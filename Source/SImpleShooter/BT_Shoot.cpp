// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"


UBT_Shoot::UBT_Shoot()
{
    //생성자에서 노드 이름 설정.
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBT_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    //BT에서 AAIController 가져오고, AAIController에서 APawn 가져와서 폰에 접근 
    AAIController* AIController = OwnerComp.GetAIOwner();
    if(AIController == nullptr)
        return EBTNodeResult::Failed;
    
    AShooterCharacter* ShooterCharater = Cast<AShooterCharacter>(AIController->GetPawn());
    if(ShooterCharater == nullptr)
    {
        return EBTNodeResult::Failed;
    }
        
    ShooterCharater->Shoot();
    return EBTNodeResult::Succeeded;
}

