// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotActState.h"

#include "Robot/Act/RobotActCharacter.h"
#include "Robot/AI/RobotAIController.h"
#include "Goal/PSFixedGoalToProtect.h"
#include "Core/Act/CoreActCharacter.h"
#include "Core/Act/CoreActSight.h"


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

}

void URobotActIdleState::OnLoop()
{
	Super::OnLoop();
	
	if (m_RobotActor->GetGoalActor() != nullptr) 
	{
		UE_LOG(LogClass, Log, TEXT("Change From MoveState"));
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
	
	UE_LOG(LogClass, Log, TEXT("Init MoveState"));

	// AI 컨트롤에 넘긴다.
	m_RobotAIControl->SetMoveToGoalVector(m_RobotActor->GetGoalActor()->GetActorLocation());
}

void URobotActMoveState::OnLoop()
{
	Super::OnLoop();
	
	ACoreActCharacter* core = m_RobotActor->m_Sight->GetNearCharacter();
	if (core != nullptr) 
	{
		// 타겟 객체를 넘긴다
		m_RobotActor->ChangeState(eStateID::TARGET, core);
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

	UE_LOG(LogClass, Log, TEXT("Initt targetState"));
	

	if (arg1 != nullptr) 
	{
		targetActor = (ACoreActCharacter*)arg1;
	}

	focusVec3 = m_RobotActor->GetActorLocation();
	m_RobotAIControl->SetMoveToHeroActor((class APawn*)targetActor);
	

}

void URobotActTargetState::OnLoop()
{
	Super::OnLoop();

	if (targetActor == nullptr) return;

	float dist = FVector::Distance(m_RobotActor->GetActorLocation(), focusVec3);

	// 800.f 임시
	if (dist > 800.f || targetActor->GetCurrentStateID() == eStateID::DEAD)
	{
		// 타겟에 가기 직전에 저장된 포커스 위치와 거리가 450. 거리만큼 멀어지거나.
		// 타겟 이 죽었으면 그냥 다시 리턴 합니다.
		// 타겟은 nullptr 처리르 비헤이비어 트리로 넘깁니다.
		m_RobotActor->ChangeState(eStateID::RETURN, &focusVec3, targetActor);
		m_RobotAIControl->SetMoveToHeroActor(nullptr);
		return;
	}
	//
	if (dist < m_RobotActor->m_AttackDist)
	{
		// 공격할 수 있는 거리만큼 가까워졌다면..
	}
	
}

void URobotActTargetState::OnExit(eStateID state)
{
	Super::OnExit(state);
}

/**
 Return
**/
void URobotActReturnState::OnExecute(eStateID eState, void* arg1, void* arg2)
{
	Super::OnExecute(eState, arg1, arg2);

	UE_LOG(LogClass, Log, TEXT("Initt ReturnState"));

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

		UE_LOG(LogClass, Log, TEXT("dist < 5.f"));
		return;
	}
	
	// 타겟 액터가 없거나, 혹은 죽은 상태라면 아래 시야체크 검사는 하지 않는다.
	if (targetActor == nullptr || targetActor->GetCurrentStateID() == eStateID::DEAD) return;
	
	// 리턴 중 타겟이 시야에서 사라지면 
	// 그냥 다시 무브로 넘어거 골로 간다.
	if (targetActor->m_Sight->IsInSightToCharacter(targetActor))
	{
		m_RobotActor->ChangeState(eStateID::MOVE);

		UE_LOG(LogClass, Log, TEXT("IsInSightToCharacter "));
		return;
	}	

	UE_LOG(LogClass, Log, TEXT("dist < %f"), dist);
}

void URobotActReturnState::OnExit(eStateID state)
{
	Super::OnExit(state);
}
