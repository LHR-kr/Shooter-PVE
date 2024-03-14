// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BT_ClearBlackBoardValue.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBT_ClearBlackBoardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBT_ClearBlackBoardValue();
protected:
	//UBTTaskNode의 함수를 오버라이드
	//Task가 시작될 때 호출함.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	
};
