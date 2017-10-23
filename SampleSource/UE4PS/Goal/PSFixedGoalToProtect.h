// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSFixedGoalToProtect.generated.h"

UCLASS()
class UE4PS_API APSFixedGoalToProtect : public AActor
{
	GENERATED_BODY()
	
public:	

	APSFixedGoalToProtect();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
