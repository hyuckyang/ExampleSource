// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "PSFieldRobotCreatePoint.generated.h"

/**
 * 
 */
UCLASS()
class UE4PS_API APSFieldRobotCreatePoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void CreateRobots(int waveNumber = -1);

	void testcreatefunc();
	FTimerHandle inoutHandle;
	
};
