// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroActState.h"
#include "Hero/Act/HeroActCharacter.h"

/**
 기본 
**/
void UHeroActState::SetCharacter(ACoreActCharacter* character)
{
	Super::SetCharacter(character);
	
	//
	this->m_HeroActor = Cast<AHeroActCharacter>(character);
}

/**
 IDLE 
**/
void UHeroActIdleState::OnExecute(eStateID state, void* arg1, void* arg2)
{
	Super::OnExecute(state, arg1, arg2);

	m_HeroActor->SetMoveForward(0.f);
	m_HeroActor->SetMoveRight(0.f);
}

void UHeroActIdleState::OnLoop()
{
	Super::OnLoop();
	LoopToUserControl();

	/*if (m_HeroActor == nullptr)return;
	if (m_HeroActor->GetVelocity().IsZero() == false)
	{
		m_HeroActor->ChangeState(eStateID::MOVE);
		return;
	}*/
	


}

void UHeroActIdleState::OnExit(eStateID state)
{
	Super::OnExit(state);
}

void UHeroActIdleState::LoopToUserControl()
{
	Super::LoopToUserControl();

	switch (m_HeroActor->GetHeroControlID())
	{
	case eHeorControlID::MANUAL :

		break;
	case eHeorControlID::SEMI_AUTO:

		break;
	case eHeorControlID::AUTO:

		// 타겟 검사

		break;
	}

}

/**
 Move
**/
void UHeroActMoveState::OnExecute(eStateID state, void* arg1, void* arg2)
{
	Super::OnExecute(state, arg1, arg2);
}

void UHeroActMoveState::OnLoop()
{
	Super::OnLoop();

	/*if (m_HeroActor == nullptr)return;
	if (m_HeroActor->GetVelocity().IsZero())
	{
		m_HeroActor->ChangeState(eStateID::IDLE);
	}*/

}

void UHeroActMoveState::OnExit(eStateID state)
{
	Super::OnExit(state);
}





