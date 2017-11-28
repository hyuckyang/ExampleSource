// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Common/PSDataSchema.h"
#include "HeroAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4PS_API AHeroAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	//
	AHeroAIController(const class FObjectInitializer&  objectInitalizer);

	// 컨트롤 동기화
	virtual void Possess(class APawn* pawn) override;
	virtual void UnPossess() override;

	void StartBehaviorTree(class APawn* pawn);
	void StopBehaviorTree();

	void SetMoveToEnemyRobot(class APawn* robot);
	void SetMoveToPatrolPoint(class ATargetPoint* point);

	void SetChangeStateID(eStateID stateID);

protected:
	class UBehaviorTreeComponent*	m_HeroBTComp;
	class UBlackboardComponent*		m_HeroBBComp;
};
