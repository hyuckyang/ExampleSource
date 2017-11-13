// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotActCharacter.h"
#include "Common/PSGameInstance.h"
#include "Core/Act/CoreActSight.h"
#include "Manager/PSActorManager.h"
#include "Goal/PSFixedGoalToProtect.h"
#include "Robot/Act/RobotActState.h"
#include "Robot/AI/RobotAIController.h"

//
#include "Public/TimerManager.h"
#include "Components/SkeletalMeshComponent.h"

// 애니메이션.
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"


void ARobotActCharacter::BeginPlay()
{
	Super::BeginPlay();

	// this->AIControllerClass = ARobotAIController::StaticClass();

	UPSGameInstance* psGameInstance = Cast<UPSGameInstance>(GetGameInstance());
	if (psGameInstance != nullptr)
	{
		m_GoalActor = psGameInstance->GetGoalActor();
		m_PSGameInstance->GetActorManager()->AddToCharacter(this);
	}

	m_RAIController = Cast<ARobotAIController>(GetController());

	m_SightDist = 550.f;
	m_Sight->SetSightDistance(m_SightDist);


	if (m_RobotAttackMontage != nullptr) 
	{
		m_TimeHandleSec = m_RobotAttackMontage->SequenceLength;
	}

	m_ActorTypeID = eActorTypeID::ROBOT;
	m_TeamID = eTeamID::DARK;

	AddState(eStateID::IDLE,	NewObject<URobotActIdleState>());
	AddState(eStateID::MOVE,	NewObject<URobotActMoveState>());
	AddState(eStateID::TARGET,	NewObject<URobotActTargetState>());
	AddState(eStateID::RETURN,	NewObject<URobotActReturnState>());
	AddState(eStateID::ATTK,	NewObject<URobotActAttackState>());
	AddState(eStateID::DEATH,   NewObject<URobotActDeathState>());


	ChangeState(eStateID::IDLE);
}

void ARobotActCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARobotActCharacter::AddState(eStateID stateID, UCoreActState * state)
{
	Super::AddState(stateID, state);
}

void ARobotActCharacter::ChangeState(eStateID stateID, void * arg1, void * arg2)
{
	Super::ChangeState(stateID, arg1, arg2);

	UCoreActState* state = this->FindState(stateID);
	if (state == nullptr) return;

	eStateID oldState = eStateID::NONE;
	if (this->m_CurState != nullptr)
	{
		// 어느 상태로 가는지 알려줌
		oldState = m_CurState->GetStateID();
		this->m_CurState->OnExit(stateID);
	}

	this->m_CurState = state;
	this->m_CurState->OnExecute(oldState, arg1, arg2);
}

/*
 Animation 
*/
void ARobotActCharacter::PlayAttackAnimLoop()
{
	PlayAnimMontage(this->m_RobotAttackMontage);

	
}

void ARobotActCharacter::PlayAttackAnimStart()
{
	// 멈추고 초기화
	m_TimeHandleAttackMontage.Invalidate();

	PlayAttackAnimLoop();

	GetWorldTimerManager().SetTimer(m_TimeHandleAttackMontage, this, &ARobotActCharacter::PlayAttackAnimLoop, m_TimeHandleSec, true);
	
}

void ARobotActCharacter::PlayAttackAnimStop()
{
	GetWorldTimerManager().ClearTimer(m_TimeHandleAttackMontage);
	StopAnimMontage();
}

void ARobotActCharacter::OnDeath()
{
	// 이미 죽은 상태라면. .. 
	if (this->GetCurrentStateID() == eStateID::DEATH) return;
	
	ChangeState(eStateID::DEATH);
}