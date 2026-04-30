// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/TaskEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ATaskEnemy::ATaskEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
	if (CubeMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(CubeMesh.Object);
	}

	HealthText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthText"));
	HealthText->SetupAttachment(RootComponent);
	HealthText->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
	HealthText->SetRelativeRotation(FRotator(80.f, 0.f, 0.f));
	HealthText->SetHorizontalAlignment(EHTA_Center);
	HealthText->SetWorldSize(80.f);
	HealthText->SetTextRenderColor(FColor::Red);
}

void ATaskEnemy::BeginPlay()
{
	Super::BeginPlay();
	HealthText->SetText(FText::AsNumber(Health));
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void ATaskEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Move(DeltaTime);
	Rotate(DeltaTime);
	SearchPlayerCharacter();
}

void ATaskEnemy::Move(float DeltaTime)
{
	if (!bTracing)	return;
	
	AddActorWorldOffset(MovementDirection * MoveSpeed * DeltaTime);
}

void ATaskEnemy::Rotate(float DeltaTime)
{
	if (bTracing)	return;
	
	AddActorWorldRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
}

void ATaskEnemy::SearchPlayerCharacter()
{
	if (bTracing)	return;
	FTraceDelegate TraceDelegate;
	TraceDelegate.BindUObject(this, &ATaskEnemy::TracePlayerCharacter);

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.WorldDynamic = ECR_Block;

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.bTraceComplex = false;

	GetWorld()->AsyncLineTraceByChannel(EAsyncTraceType::Multi,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 500.f,
		ECC_Pawn,
		params,
		ResponseParams,
		&TraceDelegate
		);
}

void ATaskEnemy::TracePlayerCharacter(const FTraceHandle& TraceHandle, FTraceDatum& Datum)
{
	if (!IsValid(PlayerCharacter))	return;
	
	for (const FHitResult& Hit : Datum.OutHits)
	{
		AActor* Actor = Hit.GetActor();
	
		if (Actor != PlayerCharacter) continue;
		
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		FVector TraceDirection = PlayerLocation - GetActorLocation();
		MovementDirection = TraceDirection.GetSafeNormal();
		
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATaskEnemy::EndTracing, 3.f, false);

		bTracing = true;
		return;
	}
}

void ATaskEnemy::EndTracing()
{
	MovementDirection = FVector::ZeroVector;
	bTracing = false;
}

void ATaskEnemy::OnHit()
{
	Health -= 1;
	HealthText->SetText(FText::AsNumber(Health));

	if (Health > 0) return;

	Destroy(true);
}
