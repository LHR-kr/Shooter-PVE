// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SImpleShooterGameModeBase.h"
#include "KillEnemyAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEnemyAllGameMode : public ASImpleShooterGameModeBase
{
	GENERATED_BODY()
public:
	virtual void KillPawn(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
