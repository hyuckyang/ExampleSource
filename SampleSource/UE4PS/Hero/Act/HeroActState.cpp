// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroActState.h"
#include "Common/PSGameInstance.h"
/*
 */
#include "Hero/AI/HeroAIController.h"
#include "Hero/Act/HeroActCharacter.h"
#include "Hero/Control/HeroActControl.h"

/*
 */
#include "Core/Act/CoreActCharacter.h"
#include "Core/Component/CoreActSightSphereComponent.h"

/*
*/
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

/**
 기본 
**/
void UHeroActState::OnExecute(eStateID state, void* arg1, void* arg2)
{
	Super::OnExecute(state, arg1, arg2);

	//
	m_HeroControl = Cast<AHeroActControl>(m_psInstance->GetCamaraControlActor());
	m_HeroAI = Cast<AHeroAIController>(m_HeroActor->GetController());

}

void UHeroActState::SetCharacter(ACoreActCharacter* character)
{
	Super::SetCharacter(character);
	
	//
	this->m_HeroActor = Cast<AHeroActCharacter>(character);
}

/**
 IDLE 
**/
void UHeroActIdleState::OnExecute(eStateID state, void* arg1, void* arg2)
{
	Super::OnExecute(state, arg1, arg2);

	//UE_LOG(LogClass, Log, TEXT("OnExecute Idle State"));

	m_HeroActor->SetMoveForward(0.f); m_HeroActor->SetMoveRight(0.f);
}

void UHeroActIdleState::OnLoop()
{
	Super::OnLoop();
	LoopToUserControl();
}

void UHeroActIdleState::OnExit(eStateID state)
{
	Super::OnExit(state);
}

void UHeroActIdleState::LoopToUserControl()
{
	Super::LoopToUserControl();

	switch (m_HeroActor->GetHeroControlID())
	{
	case eHeorControlID::MANUAL :
		
		if (!m_HeroActor->GetMoveDir().IsZero())
		{
			m_HeroActor->ChangeState(eStateID::MOVE);
		}

		break;
	case eHeorControlID::SEMI_AUTO:

		break;
	case eHeorControlID::AUTO:
		break;
	}

}

/**
 Move
**/
void UHeroActMoveState::OnExecute(eStateID state, void* arg1, void* arg2)
{
	Super::OnExecute(state, arg1, arg2);
}

void UHeroActMoveState::OnLoop()
{
	Super::OnLoop();

	if (m_HeroActor->GetMoveDir().IsZero())
	{
		m_HeroActor->ChangeState(eStateID::IDLE);
	}
}

void UHeroActMoveState::OnExit(eStateID state)
{
	Super::OnExit(state);
}



/**
 AI Patrol
**/
void UHeroActPatrolState::OnExecute(eStateID state, void* arg1, void* arg2)
{
	Super::OnExecute(state, arg1, arg2);
}

void UHeroActPatrolState::OnLoop()
{
	Super::OnLoop();

	ACoreActCharacter* core = m_HeroActor->m_SightComp->GetNearCharacter();
	if (core != nullptr) 
	{
		if (!m_HeroActor->IsEnermy(core)) return;

		switch (m_HeroActor->GetHeroControlID())
		{
			case eHeorControlID::MANUAL:
			case eHeorControlID::SEMI_AUTO:
			{
				break;
			}
			
			default:
			{
				m_HeroActor->ChangeState(eStateID::TARGET, core);
				break;
			}	
		};
	}
}

void UHeroActPatrolState::OnExit(eStateID state)
{
	Super::OnExit(state);
}

/**
 AI Tatget
**/
void UHeroActTargetState::OnExecute(eStateID state, void* arg1, void* arg2)
{
	Super::OnExecute(state, arg1, arg2);

	if (arg1 != nullptr)
	{
		targetActor = (ACoreActCharacter*)arg1;

		m_HeroAI->SetMoveToEnemyRobot(targetActor);
	}
}

void UHeroActTargetState::OnLoop()
{
	Super::OnLoop();

	if (!IsValid(targetActor) || targetActor->GetCurrentStateID() == eStateID::DEATH)
	{
		// 타겟이 죽거나 혹은 메모리에 없다면
		m_HeroActor->ChangeState(eStateID::PATROL);
		return;
	}

	// 공격 거리에 있고 (원거리 에서 체크하기에) 시야에 적이 있다면
	float dist = FVector::Distance(m_HeroActor->GetActorLocation(), targetActor->GetActorLocation());
	if (dist < m_HeroActor->m_AttackDist)
	{
		if (!m_HeroActor->IsInSight(targetActor)) return;

		m_HeroActor->ChangeState(eStateID::ATTK, targetActor);

		return;
	}
}

void UHeroActTargetState::OnExit(eStateID state)
{
	Super::OnExit(state);
}

/**
 Attack
**/
void UHeroActAttackState::OnExecute(eStateID state, void* arg1, void* arg2)
{
	Super::OnExecute(state, arg1, arg2);

	fireTimeHandle.Invalidate();
	m_HeroActor->GetWorldTimerManager().ClearTimer(fireTimeHandle);

	if (arg1 != nullptr) targetActor = (ACoreActCharacter*)arg1;

	switch (m_HeroActor->GetHeroControlID())
	{

		case eHeorControlID::MANUAL:
		case eHeorControlID::SEMI_AUTO:
		{
			// AI 아님. .. 추후에.. 처리 예정
			break;
		}

		default:
		{
			switch (m_HeroActor->GetWeaponTriggerID())
			{
				case eWeaponTriggerID::SEMIAUTO:
				case eWeaponTriggerID::BURST:
				{
					OneFrameFire();

					// UE_LOG(LogClass, Log, TEXT("OneFrameFire Start"));
					break;
				}
			}
			break;
		}
	}

	// 임시. 비헤이비어 트리 더 공부해서 아래 함수 삭제해야 함
	// m_HeroAI->SetMoveToEnemyRobot(nullptr);

	//
	// m_HeroAI->StopMovement();
}

void UHeroActAttackState::OnLoop()
{
	Super::OnLoop();

	if (!IsValid(targetActor) || targetActor->GetCurrentStateID() == eStateID::DEATH)
	{
		// 타겟이 죽거나 혹은 메모리에 없다면
		m_HeroActor->ChangeState(eStateID::PATROL);
	}

	// 다시 멀어지면 쫒아가기
	float dist = FVector::Distance(m_HeroActor->GetActorLocation(), targetActor->GetActorLocation());
	if (dist > m_HeroActor->m_AttackDist)
	{
		m_HeroActor->ChangeState(eStateID::TARGET, targetActor);
		return;
	}

	/*
	*/
	if (m_HeroActor->GetHeroControlID() != eHeorControlID::AUTO) return;
	if (m_HeroActor->GetWeaponTriggerID() != eWeaponTriggerID::FULLAUTO) return;

	m_HeroActor->OnFire(true);

	
	
}

void UHeroActAttackState::OnExit(eStateID state)
{
	Super::OnExit(state);

	m_HeroActor->OnFire(false);
}

void UHeroActAttackState::OneFrameFire()
{
	// 1초 정도로 끊어서 발사.

	if (m_HeroActor->GetCurrentStateID() != m_StateID) 
	{
		fireTimeHandle.Invalidate();
		m_HeroActor->GetWorldTimerManager().ClearTimer(fireTimeHandle);

		m_HeroActor->OnFire(false);
		return;
	}
	
	m_HeroActor->OnFire(true);
	m_HeroActor->OnFire(false);

	m_HeroActor->GetWorldTimerManager().SetTimer(
		fireTimeHandle, this, &UHeroActAttackState::OneFrameFire, 1.f, false);

	

	// UE_LOG(LogClass, Log, TEXT("OneFrameFire"));
}




