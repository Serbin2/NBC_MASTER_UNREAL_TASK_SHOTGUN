// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/GunShotgun.h"

#include "Enemy/TaskEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/GunPlayer.h"

void UGunShotgun::GunShot(FVector ShotDirection)
{
	Super::GunShot(ShotDirection);
	if (!IsValid(OwnPlayer))	return;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow,
		FString::Printf(TEXT("Shotgun Shot")));
	
	for (int i = 0; i < NumOfBullets; i++)
	{
		float RandomYaw = FMath::RandRange(-45.f, 45.f);
		FVector RotatedDirection = ShotDirection.RotateAngleAxis(RandomYaw, FVector::UpVector);
		ShotSplit(RotatedDirection);
	}
}

void UGunShotgun::ShotSplit(FVector ShotDirection)
{
	if (!IsValid(OwnPlayer))	return;
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(OwnPlayer);
	FHitResult result;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(),
		OwnPlayer->GetActorLocation(),
		OwnPlayer->GetActorLocation() + ShotDirection * 300.f,
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
