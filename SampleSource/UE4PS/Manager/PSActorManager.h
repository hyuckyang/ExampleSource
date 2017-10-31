// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	// ��ü ����� ���͵�.
	TArray<AHeroActCharacter*>	m_HeroActors;
	// ���� ��Ʈ�� �ϴ� ����� ���� -> nullptr �� �ƹ��� ��Ʈ�� ���� ����
	AHeroActCharacter*			m_ControlHeroActor;
	//������ ����
	int32						m_TapToHeroIndex = 0;

	// ���̵� �ο� �� ���� ������ ����ũ ���̵� �˻�(�ߺ��� �ȵǰ� �ϱ� ����)�� ���� ����Ʈ
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
	// �ε��� ���� �Ѱ��ش�.
	AHeroActCharacter* GetHeroActor(int index);
	// �� ���������� �ε����� ���� ����θ� ���������� �Ѱ��ݴϴ�.
	AHeroActCharacter* GetTapToHeroActor();
	// �� ���������� ��Ʈ�� ����� ���͸� �����մϴ�. -- Control ���� ���� �մϴ�.
	// void SetTapAndControlHeroActor();

	// ���� �Ʒ� �Լ��� �����ؾ� �Ѵ�.
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


};
