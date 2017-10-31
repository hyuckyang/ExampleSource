// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/PSDataSchema.h"
#include "Core/Act/CoreActCharacter.h"
#include "RobotActCharacter.generated.h"


/**
 * 
 */
UCLASS()
class UE4PS_API ARobotActCharacter : public ACoreActCharacter
{
	GENERATED_BODY()

	class ARobotAIController*		m_RAIController	= nullptr;
	class APSFixedGoalToProtect*	m_GoalActor		= nullptr;

	// class ACoreActCharacter*		m_heroActor		= nullptr;

public :

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void AddState(eStateID stateID, UCoreActState* state);
	virtual void ChangeState(eStateID stateID, void* arg1 = nullptr, void* arg2 = nullptr);

	void SetGoalActor(APSFixedGoalToProtect* goalActor) { this->m_GoalActor = goalActor; }
	APSFixedGoalToProtect* GetGoalActor() { return this->m_GoalActor; }

	ARobotAIController*  GetRobotAIContol() { return this->m_RAIController; }
public:

	UPROPERTY(EditDefaultsOnly, Category = "RobotAI")
	class UBehaviorTree* m_RobotAIBT;
	
};
