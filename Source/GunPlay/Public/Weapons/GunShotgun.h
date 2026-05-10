// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskGun.h"
#include "GunShotgun.generated.h"

UCLASS()
class GUNPLAY_API AGunShotgun : public ATaskGun
{
	GENERATED_BODY()
public:
	AGunShotgun();
	void ShotSplit(FVector ShotDirection);

protected:
	virtual void PlayEffect() override;
	virtual void ProcessFiring(FVector ShotDirection) override;

	int NumOfBullets = 5;
};
