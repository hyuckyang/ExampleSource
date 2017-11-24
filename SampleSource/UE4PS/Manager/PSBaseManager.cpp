// Fill out your copyright notice in the Description page of Project Settings.

#include "PSBaseManager.h"

UPSBaseManager::UPSBaseManager() :Super()
{

}

UWorld* UPSBaseManager::GetWorld() const
{
	return m_psGameInstance != nullptr ? m_psGameInstance->GetWorld() : nullptr;
}

