// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskGun.h"
#include "GunSniper.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UGunSniper : public UTaskGun
{
	GENERATED_BODY()
	
public:
	void GunShot(FVector ShotDirection) override;
};
