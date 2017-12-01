// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotBTTask_StrikeGoalActor.h"

/*
*/
#include "Common/PSGameInstance.h"
#include "Goal/PSFixedGoalToProtect.h"
#include "Robot/AI/RobotAIController.h"
#include "Robot/Act/RobotActCharacter.h"

/*
AI Include;
*/
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

/*
*/
EBTNodeResult::Type URobotBTTask_StrikeGoalActor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (GetWorld() == nullptr) return EBTNodeResult::Failed;

	return EBTNodeResult::Failed;

	UPSGameInstance* psGameInstance = Cast<UPSGameInstance>(GetWorld()->GetGameInstance());
	if (psGameInstance == nullptr) return EBTNodeResult::Failed;
	if (psGameInstance->GetGoalActor() == nullptr) return EBTNodeResult::Failed;

	ARobotAIController* robotAI = Cast<ARobotAIController>(OwnerComp.GetAIOwner());
	if (robotAI == nullptr) return EBTNodeResult::Failed;

	
	ARobotActCharacter* robot = Cast<ARobotActCharacter>(robotAI->GetPawn());
	if (robot == nullptr) return EBTNodeResult::Failed;

	psGameInstance->GetGoalActor()->StrikedToDamage(robot);

	return EBTNodeResult::Succeeded;
}