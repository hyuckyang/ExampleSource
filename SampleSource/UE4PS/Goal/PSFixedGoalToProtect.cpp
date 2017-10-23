// Fill out your copyright notice in the Description page of Project Settings.

#include "PSFixedGoalToProtect.h"
#include "Common/PSGameInstance.h"

APSFixedGoalToProtect::APSFixedGoalToProtect()
{
 	PrimaryActorTick.bCanEverTick = true;

	
}

void APSFixedGoalToProtect::BeginPlay()
{
	Super::BeginPlay();	

	UPSGameInstance* psGameInstance = Cast<UPSGameInstance>(GetGameInstance());
	if (psGameInstance != nullptr)
		psGameInstance->SetToGoalActor(this);
}

void APSFixedGoalToProtect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

