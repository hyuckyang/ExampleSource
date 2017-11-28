// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroBTTask_PushToPatrolPoint.h"

/*
*/
#include "Common/PSGameInstance.h"
#include "Hero/AI/HeroAIController.h"
#include "Goal/PSFixedGoalToProtect.h"

/*
*/
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"

/*
 AI Include;
*/
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UHeroBTTask_PushToPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (GetWorld() == nullptr) return EBTNodeResult::Failed;

	UPSGameInstance* psGameInstance = Cast<UPSGameInstance>(GetWorld()->GetGameInstance());
	if (psGameInstance == nullptr) return EBTNodeResult::Failed;
	if (psGameInstance->GetGoalActor() == nullptr) return EBTNodeResult::Failed;

	ATargetPoint* patrolPoint = psGameInstance->GetGoalActor()->GetPatrolPointRandom(m_CurrentPatrolIndex);
	if (patrolPoint == nullptr) return EBTNodeResult::Failed;

	AHeroAIController* heroAI = Cast<AHeroAIController>(OwnerComp.GetAIOwner());
	if (heroAI == nullptr) return EBTNodeResult::Failed;

	heroAI->SetMoveToPatrolPoint(patrolPoint);
	
	return EBTNodeResult::Succeeded;
}


