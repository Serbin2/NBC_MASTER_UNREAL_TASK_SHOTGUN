// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GunPlayer.generated.h"

class ATaskGun;
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

	void ZoomStart();
	void ZoomEnd();

	UPROPERTY(EditDefaultsOnly, Category = "Gun")
	TObjectPtr<ATaskGun> MyGun;
	TArray<TObjectPtr<ATaskGun>> Guns;
	
	UPROPERTY(EditDefaultsOnly, Category="Gun")
	TArray<TSubclassOf<ATaskGun>> GunClasses;
	
protected:
	virtual void BeginPlay() override;

private:
	void UpdateZoom(float DeltaTime);

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	bool bIsZooming = false;
	float DefaultArmLength = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float ZoomInterpSpeed = 5.f;
};
