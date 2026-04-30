// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TaskGun.generated.h"

class AGunPlayer;
/**
 * 
 */
UCLASS()
class GUNPLAY_API UTaskGun : public UObject
{
	GENERATED_BODY()	
public:
	
	UFUNCTION(BlueprintCallable, Category="Gun")
	virtual void GunShot(FVector ShotDirection);
	
	void SetOwner(AGunPlayer* Owner);
	
	UPROPERTY()
	TObjectPtr<AGunPlayer> OwnPlayer = nullptr;
};
