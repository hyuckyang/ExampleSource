// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE4PSGameModeBase.h"
#include "Common/PSDataSchema.h"
#include "PSFieldGameMode.generated.h"

class AHeroActControl;
class UFieldWindowUWidget;
class APSFixedGoalToProtect;
/**
 * 
 */
UCLASS()
class UE4PS_API APSFieldGameMode : public AUE4PSGameModeBase
{
	GENERATED_BODY()	

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// UI 셋팅
	void SetFieldWindow();
	//
	void SetGoalUpdateValue(int32 value, int32 total);
	//
	
	void WaveFlowFunc(float tick);
	void WaveFlowCreateRobots();
	void WaveStandBy();

	//
	void GameOver();
	void GameClear();
protected:
	
	APSFixedGoalToProtect*	m_GoalToProtect;
	
	AHeroActControl*		m_HeroControl;
	UFieldWindowUWidget*	m_FieldWindow;

	float					waveTicks = 0;

	eWaveTypeID				m_WaveTypeID			= eWaveTypeID::STANDBY;

	// 이거 전부 다 데이터로 빼야합니다.
	int						m_CurrentWave			= 0;
	int						m_TotalWaveNumber		= 3;
	float					m_WaveStandByTimeTick	= 3.f;
	float					m_WaveUpdateTimeTick	= 10.f;
	float					m_WaveBreakTimeTick		= 5.f;

	FTimerHandle			m_WaveTimeHandle;
	FTimerHandle			m_WaveStandByTimeHandle;

	int						m_WaveStandBy			= 3;

};
