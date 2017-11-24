// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Act/CoreActState.h"
#include "RobotActState.generated.h"

class ARobotActCharacter;
class ARobotAIController;
class APSFixedGoalToProtect;
/**
 * 
 */
UCLASS()
class UE4PS_API URobotActState : public UCoreActState
{
	GENERATED_BODY()

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);

	virtual void SetCharacter(ACoreActCharacter* character);

protected :

	ARobotActCharacter* m_RobotActor;
	ARobotAIController* m_RobotAIControl;
};

/*
 *
 */
UCLASS()
class UE4PS_API URobotActIdleState : public URobotActState
{
	GENERATED_BODY()

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);

protected:
	
};

/*
 * -> 실질적으로 Goal(자폭) 하는 곳으로 가야 하는 것
 */
UCLASS()
class UE4PS_API URobotActMoveState : public URobotActState
{
	GENERATED_BODY()

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);
};


/*
 *
 */
UCLASS()
class UE4PS_API URobotActTargetState : public URobotActState
{
	GENERATED_BODY()

	ACoreActCharacter* targetActor = nullptr;

	// 타겟에게 가는 순간
	FVector focusVec3;
public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);
};

/*
 *
 */
UCLASS()
class UE4PS_API URobotActReturnState : public URobotActState
{
	GENERATED_BODY()

	// 리턴 가야 할.
	FVector returnToLocate;
	//
	ACoreActCharacter* targetActor;

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);
};

/*
 *
 */
UCLASS()
class UE4PS_API URobotActAttackState : public URobotActState
{
	GENERATED_BODY()

	ACoreActCharacter* targetActor;

	// 다시 돌아가야 할..
	FVector returnToLocate;

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);
};

/*
 *
 */
UCLASS()
class UE4PS_API URobotActDeathState : public URobotActState
{
	GENERATED_BODY()

private :

	float robotDelayDie = 0.f;

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);

	void OnRobotDestroy();
};

/*
 Game Over 시 .
 */
UCLASS()
class UE4PS_API URobotActSleepState : public URobotActState
{
	GENERATED_BODY()

private:

	

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);
};