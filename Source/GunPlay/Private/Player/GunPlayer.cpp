// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GunPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Weapons/TaskGun.h"

// Sets default values
AGunPlayer::AGunPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1200.0f;
	CameraBoom->SetRelativeRotation(FRotator(-80.0f, 0.0f, 0.0f));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	MyGun = nullptr;
}

// Called when the game starts or when spawned
void AGunPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	for (auto gun : GunClasses)
	{
		UTaskGun* pGun = NewObject<UTaskGun>(this, gun);
		pGun->SetOwner(this);
		Guns.Add(pGun);
	}
	
	if (!IsValid(MyGun) && !Guns.IsEmpty())
	{
		MyGun = Guns[0];
		CurrentIndex = 0;
	}
}

void AGunPlayer::ChangeWeapon(int IndexDir)
{
	if (IndexDir>=0) IndexDir = 1;
	else IndexDir = -1;
	
	CurrentIndex += IndexDir;
	if (CurrentIndex>=Guns.Num()) CurrentIndex = 0;
	if (CurrentIndex<0) CurrentIndex = Guns.Num()-1;
	
	MyGun = Guns[CurrentIndex];
}

// Called every frame
void AGunPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGunPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGunPlayer::Shot()
{
	if (!IsValid(MyGun)) return;

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	FHitResult HitResult;
	if (!PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult)) return;

	FVector ShotDirection = (HitResult.ImpactPoint - GetActorLocation());
	ShotDirection.Z = 0.0f;
	ShotDirection.Normalize();
	MyGun->GunShot(ShotDirection);
}

