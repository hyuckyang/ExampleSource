// Fill out your copyright notice in the Description page of Project Settings.

#include "PSGameInstance.h"
#include "Manager/PSActorManager.h"
#include "Manager/PSWidgetManager.h"
#include "TargetPoint/PSFieldRobotCreatePoint.h"
#include "Goal/PSFixedGoalToProtect.h"
#include "Core/Camera/CoreCameraControl.h"

void UPSGameInstance::Init()
{
	// 
	CreateManagerObeject();
}

void UPSGameInstance::StartGameInstance()
{

}

void UPSGameInstance::CreateManagerObeject()
{
	this->m_ActorManager = NewObject<UPSActorManager>();
	this->m_ActorManager->AddToRoot();
	this->m_ActorManager->SetPSGameInstance(this);
	
	this->m_WidgetManager = NewObject<UPSWidgetManager>();
	this->m_WidgetManager->AddToRoot();
	this->m_WidgetManager->SetPSGameInstance(this);

}

void UPSGameInstance::OnWaveCreateRobots(int waveNumber) 
{
	if (m_FieldCreatePoints.Num() == 0) return;


	for (int loop = 0, max = m_FieldCreatePoints.Num(); loop < max; loop++)
	{
		m_FieldCreatePoints[loop]->CreateRobots(waveNumber);

		
	}


}



