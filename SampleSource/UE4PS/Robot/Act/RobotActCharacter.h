// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Act/CoreActCharacter.h"
#include "Common/PSDataSchema.h"
#include "RobotActCharacter.generated.h"

class APSFixedGoalToProtect;
/**
 * 
 */
UCLASS()
class UE4PS_API ARobotActCharacter : public ACoreActCharacter
{
	GENERATED_BODY()

	APSFixedGoalToProtect* m_GoalActor = nullptr;
public :

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void AddState(eStateID stateID, UCoreActState* state);
	virtual void ChangeState(eStateID stateID, void* arg1 = nullptr, void* arg2 = nullptr);

	void SetGoalActor(APSFixedGoalToProtect* goalActor) { this->m_GoalActor = goalActor; }
	

};
