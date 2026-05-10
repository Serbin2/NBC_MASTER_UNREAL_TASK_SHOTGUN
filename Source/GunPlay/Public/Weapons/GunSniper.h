// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskGun.h"
#include "GunSniper.generated.h"

UCLASS()
class GUNPLAY_API AGunSniper : public ATaskGun
{
	GENERATED_BODY()

protected:
	virtual void PlayEffect() override;
	virtual void ProcessFiring(FVector ShotDirection) override;
};
