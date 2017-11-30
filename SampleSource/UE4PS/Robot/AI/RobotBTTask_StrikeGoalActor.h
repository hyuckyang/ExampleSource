// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "RobotBTTask_StrikeGoalActor.generated.h"

/**
 * 
 */
UCLASS()
class UE4PS_API URobotBTTask_StrikeGoalActor : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
