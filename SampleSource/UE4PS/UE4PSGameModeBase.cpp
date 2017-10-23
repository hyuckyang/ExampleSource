// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4PSGameModeBase.h"
#include "PSPlayerController.h"
#include "Common/PSGameInstance.h"
#include "Manager/PSActorManager.h"
#include "Manager/PSWidgetManager.h"

void AUE4PSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	this->m_psGameInstance	= Cast<UPSGameInstance>(GetGameInstance());
	this->m_psActorManager	= m_psGameInstance->GetActorManager();
	this->m_psWidgetManager	= m_psGameInstance->GetWidgetManager();

	this->m_psController	= Cast<APSPlayerController>(GetWorld()->GetFirstPlayerController());
}

void AUE4PSGameModeBase::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);
}

void AUE4PSGameModeBase::SetViewFadeOut(float time) 
{
	if (m_psController == nullptr) return;

	m_psController->ClientSetCameraFade(true, FColor::Black, FVector2D(1.0, 0.0), time);
}




