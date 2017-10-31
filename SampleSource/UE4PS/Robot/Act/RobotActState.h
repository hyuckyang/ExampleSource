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
 * -> ���������� Goal(����) �ϴ� ������ ���� �ϴ� ��
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

	// Ÿ�ٿ��� ���� ����
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

	// ���� ���� ��.
	FVector returnToLocate;
	//
	ACoreActCharacter* targetActor;

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);
};

///*
// *
// */
//UCLASS()
//class UE4PS_API URobotActAttackState : public URobotActState
//{
//	GENERATED_BODY()
//
//
//public:
//	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
//	void OnLoop();
//	void OnExit(eStateID eState);
//};
