// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIShoterController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AAIShoterController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool IsDead();
private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float DetectRadius = 300.f;
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;
};
