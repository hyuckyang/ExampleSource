// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotActCharacter.h"
#include "Common/PSGameInstance.h"
#include "Core/Act/CoreActSight.h"
#include "Manager/PSActorManager.h"
#include "Goal/PSFixedGoalToProtect.h"
#include "Robot/Act/RobotActState.h"
#include "Robot/AI/RobotAIController.h"



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

	AddState(eStateID::IDLE,	NewObject<URobotActIdleState>());
	AddState(eStateID::MOVE,	NewObject<URobotActMoveState>());
	AddState(eStateID::TARGET,	NewObject<URobotActTargetState>());
	AddState(eStateID::RETURN,	NewObject<URobotActReturnState>());

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
