// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreActState.h"

UWorld* UCoreActState::GetWorld() const
{
	return m_psInstance != nullptr ? m_psInstance->GetWorld() : nullptr;
}


