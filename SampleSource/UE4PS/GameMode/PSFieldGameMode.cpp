// Fill out your copyright notice in the Description page of Project Settings.

#include "PSFieldGameMode.h"
#include "Manager/PSActorManager.h"
#include "Manager/PSWidgetManager.h"
#include "Hero/Act/HeroActCharacter.h"
#include "Hero/Control/HeroActControl.h"
#include "UMG/Window/FieldWindowUWidget.h"

void APSFieldGameMode::BeginPlay()
{
	Super::BeginPlay();

	//
	SetViewFadeOut(5.f);

	m_HeroControl = Cast<AHeroActControl>(m_psGameInstance->GetCamaraControlActor());
	if (m_HeroControl == nullptr) return;

	//
	this->SetFieldWindow();

	// 임시로 0번째 객체를 컨트롤 객체로 초기화 함
	AHeroActCharacter* heroActor = m_psActorManager->GetHeroActor(0);
	m_HeroControl->SetHeroSelected(heroActor);
	

}

void APSFieldGameMode::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if(ticks != -1)
		ticks++;

	if (ticks > 15)
	{
		m_psGameInstance->OnWaveCreateRobots(-1);
		ticks = -1;
	}
	
}

void APSFieldGameMode::SetFieldWindow()
{
	m_psWidgetManager->PushToWindow(eWindowID::Field);

	m_FieldWindow = Cast<UFieldWindowUWidget>(m_psWidgetManager->GetTopWindow());
	if (m_FieldWindow == nullptr) return;

	//
	m_FieldWindow->SetToControlMode(m_HeroControl->GetCameraControlID());

	for (int loop = 0, max = m_psActorManager->GetRegisterHeroCount(); loop < max; ++loop) 
	{
		m_FieldWindow->AddToHeroInfo(m_psActorManager->GetHeroActor(loop));
	}

	//m_FieldWindow->SelectToHeroInfo(m_)
}