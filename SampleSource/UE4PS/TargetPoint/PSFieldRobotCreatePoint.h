// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "PSFieldRobotCreatePoint.generated.h"

class UFieldWindowUWidget;
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

	void SpawnToRobot();

protected:

	UFieldWindowUWidget*	m_FieldWindow;
	FTimerHandle			m_WaveTimeHandle;
	
	int32					m_CreateValue = 3;
	int32					m_CreateCount = 0;

	
};
