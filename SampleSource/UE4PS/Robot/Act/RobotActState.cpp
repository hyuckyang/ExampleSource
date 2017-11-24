// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotActState.h"

#include "Robot/Act/RobotActCharacter.h"
#include "Robot/AI/RobotAIController.h"
#include "Goal/PSFixedGoalToProtect.h"
#include "Core/Act/CoreActCharacter.h"
#include "Core/Act/CoreActSight.h"
#include "Core/Component/CoreActSightSphereComponent.h"

/**
 기본
**/
void URobotActState::OnExecute(eStateID state, void* arg1, void* arg2)
{
	Super::OnExecute(state, arg1, arg2);
}


void URobotActState::SetCharacter(ACoreActCharacter* character)
{
	Super::SetCharacter(character);

	//
	this->m_RobotActor = Cast<ARobotActCharacter>(character);
	this->m_RobotAIControl = m_RobotActor->GetRobotAIContol();
}

/**
 IDLE -> 맨처음 상태 -> 다시 아이들로 넘어올 경우는 없다. 골검색, 이동, 자폭
**/
void URobotActIdleState::OnExecute(eStateID eState, void* arg1, void* arg2)
{
	Super::OnExecute(eState, arg1, arg2);
	UE_LOG(LogClass, Log, TEXT("Robot IDLE"));
}

void URobotActIdleState::OnLoop()
{
	Super::OnLoop();
	
	if (m_RobotActor->GetGoalActor() != nullptr) 
	{
		//(LogClass, Log, TEXT("Change From MoveState"));
		m_RobotActor->ChangeState(eStateID::MOVE);
	}
}

void URobotActIdleState::OnExit(eStateID state)
{
	Super::OnExit(state);
}


/**
 MOVE
**/
void URobotActMoveState::OnExecute(eStateID eState, void* arg1, void* arg2)
{
	Super::OnExecute(eState, arg1, arg2);
	
	// UE_LOG(LogClass, Log, TEXT("RobotActState Move || X - %f / X - %f / X - %f"), m_RobotActor->GetGoalActor()->GetActorLocation().X, m_RobotActor->GetGoalActor()->GetActorLocation().Y, m_RobotActor->GetGoalActor()->GetActorLocation().Z);

	// AI 컨트롤에 넘긴다.
	m_RobotAIControl->SetMoveToGoalVector(m_RobotActor->GetGoalActor()->GetActorLocation());
}

void URobotActMoveState::OnLoop()
{
	Super::OnLoop();
	
	ACoreActCharacter* core = m_RobotActor->m_SightComp->GetNearCharacter();

	if (core != nullptr) 
	{
		if (!m_RobotActor->IsEnermy(core)) return;

		// 타겟 객체를 넘긴다
		m_RobotActor->ChangeState(eStateID::TARGET, core);

		// UE_LOG(LogClass, Log, TEXT("RobotActState Move Next Target"));
	}
}

void URobotActMoveState::OnExit(eStateID state)
{
	Super::OnExit(state);
}

/**
 TARGET
**/
void URobotActTargetState::OnExecute(eStateID eState, void* arg1, void* arg2)
{
	Super::OnExecute(eState, arg1, arg2);

	UE_LOG(LogClass, Log, TEXT("Robot Target"));

	if (arg1 != nullptr) 
	{
		targetActor = (ACoreActCharacter*)arg1;
	}

	// 이미 돌아갈 로테이션이 정해져 있다면. 없으면 현재 위치를 돌아갈 장소로. 
	if (arg2 != nullptr)
	{
		focusVec3 = *((FVector*)arg2);
	}
	else
	{
		focusVec3 = m_RobotActor->GetActorLocation();
	}

	m_RobotAIControl->SetMoveToHeroActor((class APawn*)targetActor);
}

void URobotActTargetState::OnLoop()
{
	Super::OnLoop();

	if (targetActor == nullptr) return;

	float dist = FVector::Distance(m_RobotActor->GetActorLocation(), focusVec3);

	// 800.f 임시
	if (dist > 800.f || targetActor->GetCurrentStateID() == eStateID::DEATH)
	{
		// 타겟에 가기 직전에 저장된 포커스 위치와 거리가 450. 거리만큼 멀어지거나.
		// 타겟 이 죽었으면 그냥 다시 리턴 합니다.
		// 타겟은 nullptr 처리르 비헤이비어 트리로 넘깁니다.
		m_RobotActor->ChangeState(eStateID::RETURN, &focusVec3, targetActor);
		m_RobotAIControl->SetMoveToHeroActor(nullptr);
		return;
	}
	//

	// 타겟과 공격 가능 거리 만큼 가까워 졌다면.
	// 160. 도는 임시 입니다.
	dist = FVector::Distance(m_RobotActor->GetActorLocation(), targetActor->GetActorLocation());
	if (dist < m_RobotActor->m_AttackDist /*&& m_RobotActor->IsInAngle(targetActor, 160.f)*/)
	{
		m_RobotActor->ChangeState(eStateID::ATTK, targetActor, &focusVec3);
	}
	
}

void URobotActTargetState::OnExit(eStateID state)
{
	Super::OnExit(state);

	targetActor = nullptr;
}

/**
 Return
**/
void URobotActReturnState::OnExecute(eStateID eState, void* arg1, void* arg2)
{
	Super::OnExecute(eState, arg1, arg2);

	//UE_LOG(LogClass, Log, TEXT("Initt ReturnState"));

	if (arg1 != nullptr) returnToLocate = *((FVector*)arg1);
	if (arg2 != nullptr) targetActor = (ACoreActCharacter*)arg2;

	m_RobotAIControl->SetMoveToGoalVector(returnToLocate);
}

void URobotActReturnState::OnLoop()
{
	Super::OnLoop();


	float dist = FVector::Distance(m_RobotActor->GetActorLocation(), returnToLocate);

	// 60 은 임시임
	if (dist < 60.f) 
	{
		// 타겟을 쫒기 직전 위치까지 갔다면
		m_RobotActor->ChangeState(eStateID::MOVE);

		//UE_LOG(LogClass, Log, TEXT("dist < 5.f"));
		return;
	}
	
	// 타겟 액터가 없거나, 혹은 죽은 상태라면 아래 시야체크 검사는 하지 않는다.
	if (targetActor == nullptr || targetActor->GetCurrentStateID() == eStateID::DEATH) return;
	
	// 리턴 중 타겟이 시야에서 사라지면 
	// 그냥 다시 무브로 넘어거 골로 간다.
	if (targetActor->m_SightComp->IsInSightToCharacter(targetActor))
	{
		m_RobotActor->ChangeState(eStateID::MOVE);
		return;
	}	
}

void URobotActReturnState::OnExit(eStateID state)
{
	Super::OnExit(state);

	targetActor = nullptr;
}

/**
 Attack
**/
void URobotActAttackState::OnExecute(eStateID eState, void* arg1, void* arg2)
{
	Super::OnExecute(eState, arg1, arg2);
	if (arg1 != nullptr) targetActor = (ACoreActCharacter*)arg1;
	if (arg2 != nullptr) returnToLocate = m_RobotActor->GetActorLocation();

	m_RobotActor->PlayAttackAnimStart();

	UE_LOG(LogClass, Log, TEXT("Robot Attack"));
}

void URobotActAttackState::OnLoop()
{
	Super::OnLoop();

	if (targetActor == nullptr) return;

	float dist = FVector::Distance(m_RobotActor->GetActorLocation(), returnToLocate);
	if (dist > 800.f || targetActor->GetCurrentStateID() == eStateID::DEATH)
	{
		// 함수화.. 
		// 돌아가라..
		
		m_RobotActor->ChangeState(eStateID::RETURN, &returnToLocate, targetActor);
		m_RobotAIControl->SetMoveToHeroActor(nullptr);
		return;
	}

	// 다시 멀어지면 타겟상태로.
	dist = FVector::Distance(m_RobotActor->GetActorLocation(), targetActor->GetActorLocation());
	if (dist > m_RobotActor->m_AttackDist)
	{
		
		m_RobotActor->ChangeState(eStateID::TARGET, targetActor, &returnToLocate);
		
		return;

	}

}

void URobotActAttackState::OnExit(eStateID state)
{
	Super::OnExit(state);

	m_RobotActor->PlayAttackAnimStop();
}

/**
 DEATH
**/
void URobotActDeathState::OnExecute(eStateID eState, void* arg1, void* arg2)
{
	Super::OnExecute(eState, arg1, arg2);

	if (arg1 != nullptr)
	{
		robotDelayDie = *(float*)arg1;
	}
	
	OnRobotDestroy();
	m_RobotActor->Destroy();
	//m_RobotActor->OnDeathToRagDollActive();
	
}

void URobotActDeathState::OnLoop()
{
	Super::OnLoop();
}

void URobotActDeathState::OnExit(eStateID state)
{
	Super::OnExit(state);
}

void URobotActDeathState::OnRobotDestroy()
{
	m_RobotActor->OnDeathToParticle();
}

/**
SLEEP -> GameOver 시
**/
void URobotActSleepState::OnExecute(eStateID eState, void* arg1, void* arg2)
{
	Super::OnExecute(eState, arg1, arg2);

	UE_LOG(LogClass, Log, TEXT("Robot Sleep"));

	m_RobotActor->UnPossessed();
}

void URobotActSleepState::OnLoop()
{
	Super::OnLoop();
}

void URobotActSleepState::OnExit(eStateID state)
{
	Super::OnExit(state);
}
