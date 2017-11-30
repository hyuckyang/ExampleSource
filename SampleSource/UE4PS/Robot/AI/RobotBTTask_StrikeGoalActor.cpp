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

	UPSGameInstance* psGameInstance = Cast<UPSGameInstance>(GetWorld()->GetGameInstance());
	if (psGameInstance == nullptr) return EBTNodeResult::Failed;
	if (psGameInstance->GetGoalActor() == nullptr) return EBTNodeResult::Failed;

	UObject* obj = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("SelfActor"));
	if (!IsValid(obj))
	{
		UE_LOG(LogClass, Log, TEXT("obj == nullptr"));
		return EBTNodeResult::Failed;
	}

	ARobotActCharacter* robot = Cast<ARobotActCharacter>(obj);
	if (robot == nullptr)
	{
		UE_LOG(LogClass, Log, TEXT("robot == nullptr"));
		return EBTNodeResult::Failed;
	}

	psGameInstance->GetGoalActor()->StrikedToDamage(robot);

	/*if (!IsValid(OwnerComp.GetOwner())) return EBTNodeResult::Failed;

	if (IsValid(OwnerComp.GetOwner()))
	{
		UE_LOG(LogClass, Log, TEXT("OwnerComp.GetOwner() name %s"), *(OwnerComp.GetOwner()->GetName()) );
		
	}

	ARobotAIController* robotAI = Cast<ARobotAIController>(OwnerComp.GetAIOwner());
	if (robotAI == nullptr)
	{
		UE_LOG(LogClass, Log, TEXT("robotAI == nullptr"));
		return EBTNodeResult::Failed;
	}

	if (robotAI->GetOwner() == nullptr)
	{
		UE_LOG(LogClass, Log, TEXT("robotAI->GetOwner == nullptr"));
	}
	
	ARobotActCharacter* robot = Cast<ARobotActCharacter>(robotAI->GetOwner());
	if (robot == nullptr) 
	{
		UE_LOG(LogClass, Log, TEXT("robot == nullptr"));
		return EBTNodeResult::Failed;
	}

	

	UE_LOG(LogClass, Log, TEXT("Strike Robot Actor"));
	psGameInstance->GetGoalActor()->StrikedToDamage(robot);*/

	/*ARobotActCharacter* robot = Cast<ARobotActCharacter>(OwnerComp.GetOwner());
	if (robot == nullptr) return EBTNodeResult::Failed;

	ARobotAIController* robotAI = Cast<ARobotAIController>(OwnerComp.GetAIOwner());
	if (robotAI == nullptr) return EBTNodeResult::Failed;*/

	return EBTNodeResult::Succeeded;
}