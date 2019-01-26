// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ItemBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ2019_API UItemBase : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// bool bActive = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//// The use function of the item.
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	//void Use();
		
};
