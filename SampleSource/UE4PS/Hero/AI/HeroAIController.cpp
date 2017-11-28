// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroAIController.h"
#include "Common/PSGameInstance.h"
#include "Hero/Act/HeroActCharacter.h"
#include "Goal/PSFixedGoalToProtect.h"

/*
*/
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"

/*
AI Include;
*/
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

/*
*/
AHeroAIController::AHeroAIController(const class FObjectInitializer& objectinitializer) : Super(objectinitializer)
{
	m_HeroBTComp = objectinitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("HeroBTComp"));
	m_HeroBBComp = objectinitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("HeroBBComp"));

}

/*
*/
void AHeroAIController::Possess(class APawn* pawn)
{
	Super::Possess(pawn);
	
	StartBehaviorTree(pawn);
}

/*
*/
void AHeroAIController::UnPossess()
{
	Super::UnPossess();

	StopBehaviorTree();
}

/*
*/
void AHeroAIController::StartBehaviorTree(APawn* pawn)
{
	AHeroActCharacter* hero = Cast<AHeroActCharacter>(pawn);
	if (hero)
	{
		if (hero->m_HeroAIBT == nullptr) return;

		m_HeroBBComp->InitializeBlackboard(*(hero->m_HeroAIBT->BlackboardAsset));
		m_HeroBTComp->StartTree(*(hero->m_HeroAIBT));
	}
}

/*
*/
void AHeroAIController::StopBehaviorTree()
{
	if (m_HeroBTComp == nullptr) return;
	m_HeroBTComp->StopTree();
}

/*
*/
void AHeroAIController::SetMoveToEnemyRobot(APawn* robot)
{
	if (m_HeroBBComp != nullptr)
	{
		m_HeroBBComp->SetValueAsObject(FName("EnemyRobot"), robot);
	}
}

/*
*/
void AHeroAIController::SetMoveToPatrolPoint(ATargetPoint* point)
{
	if (m_HeroBBComp != nullptr)
	{
		m_HeroBBComp->SetValueAsObject(FName("PatrolPoint"), point);
	}
}

/*
*/
void AHeroAIController::SetChangeStateID(eStateID stateID)
{
	if (m_HeroBBComp != nullptr)
	{
		m_HeroBBComp->SetValueAsEnum(FName("eCurrentState"), (uint8)stateID);
	}

}