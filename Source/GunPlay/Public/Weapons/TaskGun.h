// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "TaskGun.generated.h"

class AGunPlayer;

UCLASS()
class GUNPLAY_API ATaskGun : public AWeaponBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category="Gun")
	virtual void GunShot(FVector ShotDirection);

	void SetOwner(AGunPlayer* GunOwner);

	float GetRange() const { return Range; }

	UPROPERTY()
	TObjectPtr<AGunPlayer> OwnPlayer = nullptr;

protected:
	virtual bool CheckAmmo();
	virtual void PlayEffect();
	virtual void ProcessFiring(FVector ShotDirection);
	virtual void UpdateAmmo();
};
