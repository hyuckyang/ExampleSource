// Fill out your copyright notice in the Description page of Project Settings.

#include "PSFieldGameMode.h"
#include "Public/TimerManager.h"
#include "Manager/PSActorManager.h"
#include "Manager/PSWidgetManager.h"
#include "Goal/PSFixedGoalToProtect.h"
#include "Hero/Act/HeroActCharacter.h"
#include "Hero/Control/HeroActControl.h"
#include "UMG/Window/FieldWindowUWidget.h"


void APSFieldGameMode::BeginPlay()
{
	Super::BeginPlay();

	//
	SetViewFadeOut(5.f);

	m_HeroControl = Cast<AHeroActControl>(m_psGameInstance->GetCamaraControlActor());
	if (m_HeroControl == nullptr) return;

	//
	this->SetFieldWindow();

	// 임시로 0번째 객체를 컨트롤 객체로 초기화 함
	AHeroActCharacter* heroActor = m_psActorManager->GetHeroActor(0);
	m_HeroControl->SetHeroSelected(heroActor);

	
	return;


	waveTicks = 0.f;
	WaveStandBy();
}

void APSFieldGameMode::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (testTick == 3) 
	{
		m_psGameInstance->OnWaveCreateRobots(1);
	}
	testTick++;

	return;

	if (m_WaveTypeID != eWaveTypeID::END) 
	{
		WaveFlowFunc(DeltaTime);
	}

	// Goal Actor 설정 음..
	if (m_GoalToProtect == nullptr && m_psGameInstance->GetGoalActor())
	{
		
		m_GoalToProtect = m_psGameInstance->GetGoalActor();
		// Bind 설정
		m_GoalToProtect->GoalUpdateFuncBind(m_FieldWindow, &UFieldWindowUWidget::SetGoalUpdateValue);
		m_GoalToProtect->GoalUpdateFuncBind(this, &APSFieldGameMode::SetGoalUpdateValue);
	}
}

/*
 *
 */
void APSFieldGameMode::SetFieldWindow()
{
	m_psWidgetManager->PushToWindow(eWindowID::Field);

	m_FieldWindow = Cast<UFieldWindowUWidget>(m_psWidgetManager->GetTopWindow());
	if (m_FieldWindow == nullptr) return;

	//
	m_FieldWindow->SetToControlMode(m_HeroControl->GetCameraControlID());

	for (int loop = 0, max = m_psActorManager->GetRegisterHeroCount(); loop < max; ++loop) 
	{
		m_FieldWindow->AddToHeroInfo(m_psActorManager->GetHeroActor(loop));
	}
}

/*
 *
 */
void APSFieldGameMode::SetGoalUpdateValue(int32 value, int32 total)
{
	if (value == 0) 
	{
		m_WaveTypeID = eWaveTypeID::END;
		GameOver();
		return;
	}
}

/*
 *
 */
void APSFieldGameMode::WaveFlowFunc(float tick)
{
	waveTicks += tick;

	switch (m_WaveTypeID) 
	{
		case eWaveTypeID::STANDBY:
		{
			

			if (waveTicks >= m_WaveStandByTimeTick)
			{
				// UE_LOG(LogClass, Log, TEXT("eWaveTypeID::STANDBY OUT"));
				//
				m_WaveTypeID = eWaveTypeID::UPDATE;
				waveTicks = 0.f;

				m_CurrentWave++;
				m_FieldWindow->SetWaveInfoTextPrint(FString::Printf(TEXT("Wave %d"), m_CurrentWave));
				WaveFlowCreateRobots();
			}
			break;
		}
		case eWaveTypeID::UPDATE:
		{
			if (waveTicks >= m_WaveUpdateTimeTick)
			{
				if (m_CurrentWave == m_TotalWaveNumber)
				{
					m_WaveTypeID = eWaveTypeID::END;

					// 게임 클리어
					GameClear();
				}
				else
				{
					m_FieldWindow->SetWaveInfoTextPrint("Break Time!");
					m_WaveTypeID = eWaveTypeID::BREAK;

					waveTicks = 0.f;
				}
			}
			break;
		}
		case eWaveTypeID::BREAK:
		{
			if (waveTicks >= m_WaveBreakTimeTick)
			{
				m_WaveTypeID = eWaveTypeID::STANDBY;
				waveTicks = 0.f;

				WaveStandBy();
			}
			break;
		}
	}	
}

/*
 *
 */
void APSFieldGameMode::WaveFlowCreateRobots()
{
	// 업데이트 가 아니라면 끝낸다.
	if (m_WaveTypeID != eWaveTypeID::UPDATE) 
	{
		m_WaveTimeHandle.Invalidate();
		GetWorldTimerManager().ClearTimer(m_WaveTimeHandle);
		return;
	}
	m_psGameInstance->OnWaveCreateRobots(m_CurrentWave);

	// 5 초 간격으로 로봇을 계속 스폰 
	GetWorldTimerManager().SetTimer(m_WaveTimeHandle, this, &APSFieldGameMode::WaveFlowCreateRobots, 5.f, false);
}

/*
 *
 */
void APSFieldGameMode::WaveStandBy()
{
	// 업데이트 가 아니라면 끝낸다.
	if (m_WaveTypeID != eWaveTypeID::STANDBY)
	{
		m_WaveStandBy = 3;
		m_WaveStandByTimeHandle.Invalidate();
		GetWorldTimerManager().ClearTimer(m_WaveStandByTimeHandle);
		return;
	}


	m_FieldWindow->SetWaveInfoTextPrint(FString::Printf(TEXT("%d"), m_WaveStandBy));
	m_WaveStandBy--;

	//
	GetWorldTimerManager().SetTimer(m_WaveStandByTimeHandle, this, &APSFieldGameMode::WaveStandBy, 1.f, false);	
}

/*
 *
 */
void APSFieldGameMode::GameOver()
{
	m_psActorManager->TotalActChangeState(eStateID::SLEEP);

	// m_FieldWindow->SetWaveInfoTextPrint("Game Over");

	FString str = FString("Game Over");
	m_psWidgetManager->PushToWindow(eWindowID::End, &str);
}

/*
 *
 */
void APSFieldGameMode::GameClear()
{
	m_psActorManager->TotalActChangeState(eStateID::SLEEP);

	// m_FieldWindow->SetWaveInfoTextPrint("Game Clear");

	FString str = FString("Game Clear");
	m_psWidgetManager->PushToWindow(eWindowID::End, &str);
}
