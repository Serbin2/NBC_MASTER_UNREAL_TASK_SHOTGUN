// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GunPlayer.generated.h"

class UTaskGun;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class GUNPLAY_API AGunPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AGunPlayer();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Gun")
	void Shot();
	
	void ChangeWeapon(int IndexDir);
	int CurrentIndex = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Gun")
	TObjectPtr<UTaskGun> MyGun;
	TArray<TObjectPtr<UTaskGun>> Guns;
	
	UPROPERTY(EditDefaultsOnly, Category="Gun")
	TArray<TSubclassOf<UTaskGun>> GunClasses;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
