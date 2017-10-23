// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Common/PSDataSchema.h"
#include "CoreActState.generated.h"

class  ACoreActCharacter;
/**
 * 
 */
UCLASS()
class UE4PS_API UCoreActState : public UObject
{
	GENERATED_BODY()

public:

	virtual void OnExecute(eStateID eState, void* arg1 = nullptr, void* arg2 = nullptr) {};
	virtual void OnLoop() {};
	virtual void OnExit(eStateID eState) {};


	virtual void SetCharacter(ACoreActCharacter* character) { this->m_MineCharacter = character; }
	virtual eStateID GetStateID() { return m_StateID; }

	void SetStateID(eStateID state) { this->m_StateID = state; }

protected:
	ACoreActCharacter* m_MineCharacter;
	eStateID		   m_StateID;

};
