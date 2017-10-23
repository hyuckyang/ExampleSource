// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotActCharacter.h"
#include "Common/PSGameInstance.h"
#include "Goal/PSFixedGoalToProtect.h"
#include "Robot/AI/RobotAIController.h"
#include "Core/Act/CoreActSight.h"

void ARobotActCharacter::BeginPlay()
{
	Super::BeginPlay();

	// this->AIControllerClass = ARobotAIController::StaticClass();

	UPSGameInstance* psGameInstance = Cast<UPSGameInstance>(GetGameInstance());
	if (psGameInstance != nullptr)
	{
		m_GoalActor = psGameInstance->GetGoalActor();
	}

	m_SightDist = 150.f;
	m_Sight->SetSightDistance(m_SightDist);

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
}
