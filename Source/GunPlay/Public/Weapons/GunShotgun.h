// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskGun.h"
#include "GunShotgun.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UGunShotgun : public UTaskGun
{
	GENERATED_BODY()
public:
	void GunShot(FVector ShotDirection) override;
	void ShotSplit(FVector ShotDirection);
	
protected:
	int NumOfBullets = 5;
};
