// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/TaskGun.h"
#include "Player/GunPlayer.h"

void ATaskGun::GunShot(FVector ShotDirection)
{
	if (!CanFire) return;

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow,
		FString::Printf(TEXT("ShotDirection: X=%.2f Y=%.2f Z=%.2f"), ShotDirection.X, ShotDirection.Y, ShotDirection.Z));

	if (CheckAmmo())
	{
		PlayEffect();
		ProcessFiring(ShotDirection);
		UpdateAmmo();
		Super::Fire();
	}
}

void ATaskGun::SetOwner(AGunPlayer* GunOwner)
{
	OwnPlayer = GunOwner;
}

bool ATaskGun::CheckAmmo()
{
	return CurrentAmmo >= AmmoPerFire;
}

void ATaskGun::PlayEffect()
{
}

void ATaskGun::ProcessFiring(FVector ShotDirection)
{
}

void ATaskGun::UpdateAmmo()
{
	CurrentAmmo -= AmmoPerFire;
}
