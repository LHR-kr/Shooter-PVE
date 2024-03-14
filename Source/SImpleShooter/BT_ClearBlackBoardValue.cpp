// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_ClearBlackBoardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_ClearBlackBoardValue::UBT_ClearBlackBoardValue()
{
    NodeName = TEXT("Clear BlackBoard Value");
}

//오버라이딩
EBTNodeResult::Type UBT_ClearBlackBoardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    
    Super::ExecuteTask(OwnerComp, NodeMemory);

    //BT에 접근해서 BB를 가져오고, 블랙보드 키 값을 수정.
    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    return EBTNodeResult::Succeeded;
}
