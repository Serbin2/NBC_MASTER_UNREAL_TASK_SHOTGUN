// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/GunShotgun.h"

#include "Enemy/TaskEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/GunPlayer.h"

AGunShotgun::AGunShotgun()
{
	Range = 300.f;
	MaxAmmo = 20;
}

void AGunShotgun::PlayEffect()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Shotgun Shot"));
}

void AGunShotgun::ProcessFiring(FVector ShotDirection)
{
	if (!IsValid(OwnPlayer)) return;

	for (int i = 0; i < NumOfBullets; i++)
	{
		float RandomYaw = FMath::RandRange(-45.f, 45.f);
		FVector RotatedDirection = ShotDirection.RotateAngleAxis(RandomYaw, FVector::UpVector);
		ShotSplit(RotatedDirection);
	}
}

void AGunShotgun::ShotSplit(FVector ShotDirection)
{
	if (!IsValid(OwnPlayer))	return;
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(OwnPlayer);
	FHitResult result;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(),
		OwnPlayer->GetActorLocation(),
		OwnPlayer->GetActorLocation() + ShotDirection * Range,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,actorsToIgnore,
		EDrawDebugTrace::ForDuration, result,
		true,FLinearColor::Red,FLinearColor::Green,
		2.f
		);
	
	if (AActor* HitActor = result.GetActor())
	{
		ATaskEnemy* Enemy = Cast<ATaskEnemy>(HitActor);
		if (IsValid(Enemy))
		{
			Enemy->OnHit();
		}
	}
}
