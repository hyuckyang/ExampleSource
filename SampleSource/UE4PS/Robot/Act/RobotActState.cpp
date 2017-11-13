// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotActState.h"

#include "Robot/Act/RobotActCharacter.h"
#include "Robot/AI/RobotAIController.h"
#include "Goal/PSFixedGoalToProtect.h"
#include "Core/Act/CoreActCharacter.h"
#include "Core/Act/CoreActSight.h"


/**
 �⺻
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
 IDLE -> ��ó�� ���� -> �ٽ� ���̵�� �Ѿ�� ���� ����. ��˻�, �̵�, ����
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
	
	//UE_LOG(LogClass, Log, TEXT("Init MoveState"));

	// AI ��Ʈ�ѿ� �ѱ��.
	m_RobotAIControl->SetMoveToGoalVector(m_RobotActor->GetGoalActor()->GetActorLocation());
}

void URobotActMoveState::OnLoop()
{
	Super::OnLoop();
	
	ACoreActCharacter* core = m_RobotActor->m_Sight->GetNearCharacter();
	if (core != nullptr) 
	{
		// Ÿ�� ��ü�� �ѱ��
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

	if (arg1 != nullptr) 
	{
		targetActor = (ACoreActCharacter*)arg1;
	}

	// �̹� ���ư� �����̼��� ������ �ִٸ�. ������ ���� ��ġ�� ���ư� ��ҷ�. 
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

	// 800.f �ӽ�
	if (dist > 800.f || targetActor->GetCurrentStateID() == eStateID::DEATH)
	{
		// Ÿ�ٿ� ���� ������ ����� ��Ŀ�� ��ġ�� �Ÿ��� 450. �Ÿ���ŭ �־����ų�.
		// Ÿ�� �� �׾����� �׳� �ٽ� ���� �մϴ�.
		// Ÿ���� nullptr ó���� �����̺�� Ʈ���� �ѱ�ϴ�.
		m_RobotActor->ChangeState(eStateID::RETURN, &focusVec3, targetActor);
		m_RobotAIControl->SetMoveToHeroActor(nullptr);
		return;
	}
	//

	// Ÿ�ٰ� ���� ���� �Ÿ� ��ŭ ����� ���ٸ�.
	// 160. ���� �ӽ� �Դϴ�.
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

	// 60 �� �ӽ���
	if (dist < 60.f) 
	{
		// Ÿ���� �i�� ���� ��ġ���� ���ٸ�
		m_RobotActor->ChangeState(eStateID::MOVE);

		//UE_LOG(LogClass, Log, TEXT("dist < 5.f"));
		return;
	}
	
	// Ÿ�� ���Ͱ� ���ų�, Ȥ�� ���� ���¶�� �Ʒ� �þ�üũ �˻�� ���� �ʴ´�.
	if (targetActor == nullptr || targetActor->GetCurrentStateID() == eStateID::DEATH) return;
	
	// ���� �� Ÿ���� �þ߿��� ������� 
	// �׳� �ٽ� ����� �Ѿ�� ��� ����.
	if (targetActor->m_Sight->IsInSightToCharacter(targetActor))
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
}

void URobotActAttackState::OnLoop()
{
	Super::OnLoop();

	if (targetActor == nullptr) return;

	float dist = FVector::Distance(m_RobotActor->GetActorLocation(), returnToLocate);
	if (dist > 800.f || targetActor->GetCurrentStateID() == eStateID::DEATH)
	{
		// �Լ�ȭ.. 
		// ���ư���..

	

		m_RobotActor->ChangeState(eStateID::RETURN, &returnToLocate, targetActor);
		m_RobotAIControl->SetMoveToHeroActor(nullptr);

		
		return;
	}

	// �ٽ� �־����� Ÿ�ٻ��·�.
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

	m_RobotActor->OnDeathToRagDollActive();
	
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

}