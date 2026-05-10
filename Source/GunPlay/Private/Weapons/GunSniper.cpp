// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/GunSniper.h"

#include "Enemy/TaskEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/GunPlayer.h"


void AGunSniper::PlayEffect()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Sniper Shot"));
}

void AGunSniper::ProcessFiring(FVector ShotDirection)
{
	if (!IsValid(OwnPlayer)) return;

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(OwnPlayer);
	TArray<FHitResult> result;

	UKismetSystemLibrary::LineTraceMulti(GetWorld(),
		OwnPlayer->GetActorLocation(),
		OwnPlayer->GetActorLocation() + ShotDirection * Range,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false, actorsToIgnore,
		EDrawDebugTrace::ForDuration, result,
		true, FLinearColor::Red, FLinearColor::Green,
		2.f
		);

	for (auto HitResult : result)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			ATaskEnemy* Enemy = Cast<ATaskEnemy>(HitActor);
			if (IsValid(Enemy))
			{
				Enemy->OnHit();
			}
		}
	}
}
