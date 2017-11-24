// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/PSDataSchema.h"
#include "Manager/PSBaseManager.h"
#include "PSActorManager.generated.h"

class ACoreActCharacter;
class AHeroActCharacter;
/**
 * 
 */
UCLASS()
class UE4PS_API UPSActorManager : public UPSBaseManager
{
	GENERATED_BODY()

	//
	TArray<ACoreActCharacter*>	m_CoreActors;
	// 전체 히어로 액터들.
	TArray<AHeroActCharacter*>	m_HeroActors;
	// 현재 컨트롤 하는 히어로 액터 -> nullptr 은 아무도 컨트롤 하지 않음
	AHeroActCharacter*			m_ControlHeroActor;
	//순차적 접근
	int32						m_TapToHeroIndex = 0;

	// 아이디 부여 시 오든 액터의 유니크 아이디 검사(중복아 안되게 하기 위해)를 위한 리스트
	TArray<int32>				m_TotalUniqueID;
public:

	virtual void SetPSGameInstance(UPSGameInstance* instance);

	/*
	Hero -
	*/
	//
	void AddToCharacter(ACoreActCharacter* core);
	void AddToHero(AHeroActCharacter* hero);
	//
	AHeroActCharacter* GetControlHeroActor();
	// 
	void SetControlHeroActor(AHeroActCharacter* hero);
	// 인덱스 별로 넘겨준다.
	AHeroActCharacter* GetHeroActor(int index);
	// 탭 누를때마다 인덱스에 따라 히어로를 순차적으로 넘겨줍니다.
	AHeroActCharacter* GetTapToHeroActor();
	// 탭 누를때마다 컨트롤 히어로 액터를 변경합니다. -- Control 에서 관리 합니다.
	// void SetTapAndControlHeroActor();

	// 추후 아래 함수는 수정해야 한다.
	int GetRegisterHeroCount() { return m_HeroActors.Num(); }
	//

	/*
	Robot
	*/

	/*
	Unique ID
	*/
	int32 GetRandomUniqueID();
	void  GiveToUniqueID(ACoreActCharacter* character);

	/*
	Total 
	*/
	void TotalActChangeState(eStateID stateID);
};
