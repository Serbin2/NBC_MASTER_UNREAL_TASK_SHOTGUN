// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaskEnemy.generated.h"

class UStaticMeshComponent;
class UTextRenderComponent;

UCLASS()
class GUNPLAY_API ATaskEnemy : public AActor
{
	GENERATED_BODY()

public:
	ATaskEnemy();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<UTextRenderComponent> HealthText;
	
	UPROPERTY()
	TObjectPtr<ACharacter> PlayerCharacter;
	
	void Move(float DeltaTime);
	void Rotate(float DeltaTime);
	void SearchPlayerCharacter();
	void TracePlayerCharacter(const FTraceHandle& TraceHandle, FTraceDatum& Datum);
	void EndTracing();

	FTimerHandle TimerHandle;
	bool bTracing = false;
	
public:
	virtual void Tick(float DeltaTime) override;

	void OnHit();
	
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MoveSpeed = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RotationSpeed = 90.f;
	
	FVector MovementDirection = FVector::ZeroVector;

	
	
	int Health = 5;
};
