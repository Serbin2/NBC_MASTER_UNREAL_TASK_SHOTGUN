// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/GunSniper.h"

#include "Enemy/TaskEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/GunPlayer.h"


void UGunSniper::GunShot(FVector ShotDirection)
{
	Super::GunShot(ShotDirection);
	if (!IsValid(OwnPlayer))	return;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow,
		FString::Printf(TEXT("Sniper Shot")));
	
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(OwnPlayer);
	TArray<FHitResult> result;

	UKismetSystemLibrary::LineTraceMulti(GetWorld(),
		OwnPlayer->GetActorLocation(),
		OwnPlayer->GetActorLocation() + ShotDirection * 1000.f,		
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,actorsToIgnore,
		EDrawDebugTrace::ForDuration, result,
		true,FLinearColor::Red,FLinearColor::Green,
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
