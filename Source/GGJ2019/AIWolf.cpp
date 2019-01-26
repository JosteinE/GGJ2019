// Fill out your copyright notice in the Description page of Project Settings.

#include "AIWolf.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAIWolf::AAIWolf()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
}

void AAIWolf::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIWolf::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AAIWolf::OnNoiseHeard);
}

// Called when the game starts or when spawned
void AAIWolf::BeginPlay()
{
	Super::BeginPlay();
	
}
void AAIWolf::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 10.0f);
}

void AAIWolf::OnNoiseHeard(APawn * NoiseInstigator, const FVector & Location, float Volume)
{
	//DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Red, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	SetActorRotation(NewLookAt);
	
}


// Called every frame
void AAIWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
