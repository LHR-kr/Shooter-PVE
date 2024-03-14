// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerIsSeen.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTService_PlayerIsSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_PlayerIsSeen();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
