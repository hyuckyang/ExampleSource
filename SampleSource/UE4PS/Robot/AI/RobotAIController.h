// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RobotAIController.generated.h"

/**
 UE4 SurvivalGame Sample -> Zombie AI �� �����Ͽ����ϴ�.
 */
UCLASS()
class UE4PS_API ARobotAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	//
	ARobotAIController(const class FObjectInitializer&  objectInitalizer);

	// ��Ʈ�� ����ȭ
	virtual void Possess(class APawn* pawn) override;
	virtual void UnPossess() override;
	
	void SetMoveToGoalVector(FVector goalVector);
	void SetMoveToHeroActor(class APawn* heroActor);

protected:

	class UBehaviorTreeComponent*	m_RobotBTComp;
	class UBlackboardComponent*		m_RobotBBComp;

};
