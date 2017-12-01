// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/TimerManager.h"
#include "Core/Act/CoreActState.h"
#include "HeroActState.generated.h"

class AHeroActControl;
class AHeroActCharacter;
class AHeroAIController;
class ACoreActCharacter;
/**
 * 
 */
UCLASS()
class UE4PS_API UHeroActState : public UCoreActState
{
	GENERATED_BODY()

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);

	virtual void SetCharacter(ACoreActCharacter* character);
	virtual void LoopToUserControl() {};

protected:
	AHeroActControl*	m_HeroControl;
	AHeroActCharacter*  m_HeroActor;
	AHeroAIController*	m_HeroAI;
	
	
	
};

/*
 *
 */
UCLASS()
class UE4PS_API UHeroActIdleState : public UHeroActState
{
	GENERATED_BODY()
public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);

	void LoopToUserControl();
	
};

/*
 *
 */
UCLASS()
class UE4PS_API UHeroActMoveState : public UHeroActState
{
	GENERATED_BODY()

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);

};

/*
 * AI . Patrol
 */
UCLASS()
class UE4PS_API UHeroActPatrolState : public UHeroActState
{
	GENERATED_BODY()

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);

};

/*
 * AI - TargetMode
 */
UCLASS()
class UE4PS_API UHeroActTargetState : public UHeroActState
{
	GENERATED_BODY()

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);

protected:
	class ACoreActCharacter* targetActor;

};

/*
 * AI And Control - Attack
 */
UCLASS()
class UE4PS_API UHeroActAttackState : public UHeroActState
{
	GENERATED_BODY()

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);

	void OneFrameFire();

protected:
	ACoreActCharacter*			targetActor;
	FTimerHandle				fireTimeHandle;
	float						fireTick		= 0.f;
};

/*

 */
UCLASS()
class UE4PS_API UHeroActSleepState : public UHeroActState
{
	GENERATED_BODY()

public:
	void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr);
	void OnLoop();
	void OnExit(eStateID eState);
};

