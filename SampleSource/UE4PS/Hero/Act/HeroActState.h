// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Act/CoreActState.h"
#include "HeroActState.generated.h"

class AHeroActControl;
class AHeroActCharacter;
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
