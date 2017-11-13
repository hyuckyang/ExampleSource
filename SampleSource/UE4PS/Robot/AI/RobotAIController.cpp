// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotAIController.h"
#include "Common/PSGameInstance.h"
#include "Goal/PSFixedGoalToProtect.h"
#include "Robot/Act/RobotActCharacter.h"

/*
AI Include;
*/
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

/*

*/
ARobotAIController::ARobotAIController(const class FObjectInitializer& objectinitializer) : Super(objectinitializer)
{
	m_RobotBTComp = objectinitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("RobotBTComp"));
	m_RobotBBComp = objectinitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("RobotBBComp"));
}

/*
*/
void ARobotAIController::Possess(class APawn* pawn)
{
	Super::Possess(pawn);

	return;
	ARobotActCharacter* robot = Cast<ARobotActCharacter>(pawn);
	if (robot)
	{
		if (robot->m_RobotAIBT == nullptr) return;

		m_RobotBBComp->InitializeBlackboard(*(robot->m_RobotAIBT->BlackboardAsset));
		m_RobotBTComp->StartTree(*(robot->m_RobotAIBT));
	}
}

/*

*/
void ARobotAIController::UnPossess()
{
	Super::UnPossess();

	m_RobotBTComp->StopTree();
}

/*

*/
void ARobotAIController::SetMoveToGoalVector(FVector goalVector)
{
	if (m_RobotBBComp != nullptr)
	{
		m_RobotBBComp->SetValueAsVector(FName("MoveToGoalVector"), goalVector);
	}
}

/*

*/
void ARobotAIController::SetMoveToHeroActor(class APawn* heroActor)
{
	if (m_RobotBBComp != nullptr)
	{
		m_RobotBBComp->SetValueAsObject(FName("HeroActor"), heroActor);
	}
}