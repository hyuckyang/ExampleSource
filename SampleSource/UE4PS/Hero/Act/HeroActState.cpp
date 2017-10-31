// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroActState.h"
#include "Common/PSGameInstance.h"
#include "Hero/Act/HeroActCharacter.h"
#include "Hero/Control/HeroActControl.h"

/**
 ±âº» 
**/
void UHeroActState::OnExecute(eStateID state, void* arg1, void* arg2)
{
	Super::OnExecute(state, arg1, arg2);

	//
	m_HeroControl = Cast<AHeroActControl>(m_psInstance->GetCamaraControlActor());

}

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

	//UE_LOG(LogClass, Log, TEXT("OnExecute Idle State"));

	m_HeroActor->SetMoveForward(0.f); m_HeroActor->SetMoveRight(0.f);
}

void UHeroActIdleState::OnLoop()
{
	Super::OnLoop();
	LoopToUserControl();
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
		
		if (!m_HeroActor->GetMoveDir().IsZero())
		{
			m_HeroActor->ChangeState(eStateID::MOVE);
		}

		break;
	case eHeorControlID::SEMI_AUTO:

		break;
	case eHeorControlID::AUTO:
		break;
	}

}

/**
 Move
**/
void UHeroActMoveState::OnExecute(eStateID state, void* arg1, void* arg2)
{
	Super::OnExecute(state, arg1, arg2);

	//UE_LOG(LogClass, Log, TEXT("OnExecute Run State"));
}

void UHeroActMoveState::OnLoop()
{
	Super::OnLoop();

	//if (m_HeroActor == nullptr)return;
	//if (m_HeroActor->GetVelocity().IsZero())
	//{
	//	//UE_LOG(LogClass, Log, TEXT("Change Run To Idle"));
	//	m_HeroActor->ChangeState(eStateID::IDLE);
	//}

	if (m_HeroActor->GetMoveDir().IsZero())
	{
		m_HeroActor->ChangeState(eStateID::IDLE);
	}

}

void UHeroActMoveState::OnExit(eStateID state)
{
	Super::OnExit(state);
}





