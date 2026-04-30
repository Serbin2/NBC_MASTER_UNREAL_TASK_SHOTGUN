// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/TaskGun.h"
#include "Player/GunPlayer.h"

void UTaskGun::GunShot(FVector ShotDirection)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow,
		FString::Printf(TEXT("ShotDirection: X=%.2f Y=%.2f Z=%.2f"), ShotDirection.X, ShotDirection.Y, ShotDirection.Z));
}

void UTaskGun::SetOwner(AGunPlayer* Owner)
{
	OwnPlayer = Owner;
}
