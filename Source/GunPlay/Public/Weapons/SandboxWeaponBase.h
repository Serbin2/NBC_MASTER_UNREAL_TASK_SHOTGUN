// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "SandboxWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API ASandboxWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
public:
	virtual void Fire() override;

	UFUNCTION(BlueprintImplementableEvent)
	void SandboxFire();
	
protected:
	
	UFUNCTION(BlueprintCallable)
	void Reload();
	
	UFUNCTION(BlueprintCallable)
	bool CheckAmmo();
	
	UFUNCTION(BlueprintCallable)
	void LineTraceOneShot(FVector Direction);
	
	UFUNCTION(BlueprintCallable)
	void PlaySound(USoundBase* Sound);
	
	UFUNCTION(BlueprintCallable)
	void UpdateAmmo();
	
	
};
