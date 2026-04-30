// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/GunController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Player/GunPlayer.h"

AGunController::AGunController()
{
	bShowMouseCursor = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AGunController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AGunController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGunController::Move);
		EIC->BindAction(ShotAction, ETriggerEvent::Started, this, &AGunController::Shot);
		EIC->BindAction(ChangeWeaponAction, ETriggerEvent::Started, this, &AGunController::ChangeWeapon);
	}
}

void AGunController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateTowardMouse();
}

void AGunController::Move(const FInputActionValue& Value)
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	FVector2D MovementVector = Value.Get<FVector2D>();
	ControlledPawn->AddMovementInput(FVector::ForwardVector, MovementVector.Y);
	ControlledPawn->AddMovementInput(FVector::RightVector, MovementVector.X);
}

void AGunController::Shot()
{
	AGunPlayer* pPlayer = Cast<AGunPlayer>(GetPawn());
	if (!pPlayer) return;
	
	pPlayer->Shot();
}

void AGunController::ChangeWeapon(const FInputActionValue& Value)
{
	AGunPlayer* pPlayer = Cast<AGunPlayer>(GetPawn());
	if (!pPlayer) return;

	int IndexDir = FMath::RoundToInt(Value.Get<float>());
	pPlayer->ChangeWeapon(IndexDir);
}

void AGunController::RotateTowardMouse()
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	FHitResult HitResult;
	if (!GetHitResultUnderCursor(ECC_Visibility, false, HitResult)) return;

	FVector Direction = HitResult.ImpactPoint - ControlledPawn->GetActorLocation();
	Direction.Z = 0.0f;

	if (!Direction.IsNearlyZero())
	{
		ControlledPawn->SetActorRotation(Direction.Rotation());
	}
}
