// Fill out your copyright notice in the Description page of Project Settings.

#include "checkpoint.h"
#include "components/BoxComponent.h"
#include "Engine/World.h"
#include "GGJ2019GameMode.h"

// Sets default values
Acheckpoint::Acheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collider"));
	RootComponent = BoxCollider;
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &Acheckpoint::OnHit);
}

// Called when the game starts or when spawned
void Acheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Acheckpoint::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	auto *gamemode = GetWorld()->GetAuthGameMode<GGJ2019GameMode>();
	if (gamemode && playerController)
	{
		auto *playerStart = gamemode->FindPlayerStart(playerController);
		if (playerStart)
		{
			playerStart->SetActorLocation(FVector{ playerStart->GetActorLocation().Z, GetActorLocation().Y, GetActorLocation().Z });
			Destroy();
		}
	}
}

