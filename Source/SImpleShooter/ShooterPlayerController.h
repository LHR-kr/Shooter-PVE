// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.0f;
	FTimerHandle RestartTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LoseScreenUIClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> WinScreenUIClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HUDUIClass;
	
	UUserWidget* HUDUI;
};
