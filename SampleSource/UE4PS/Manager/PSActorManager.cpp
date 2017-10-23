// Fill out your copyright notice in the Description page of Project Settings.

#include "PSActorManager.h"
#include "Core/Act/CoreActCharacter.h"
#include "Hero/Control/HeroActControl.h"

/*

*/
void UPSActorManager::SetPSGameInstance(UPSGameInstance* instance)
{
	Super::SetPSGameInstance(instance);

	if (GetWorld() != nullptr) 
	{
		UE_LOG(LogClass, Log, TEXT("Base GameInstance GetWorld not nullptr"));
	}

	// 초기화를 시도 합니다.
	m_ControlHeroActor = nullptr;
}

/*

*/
void UPSActorManager::AddToHero(AHeroActCharacter* hero)
{
	// 유니크 아이디 부여
	GiveToUniqueID((ACoreActCharacter*)(hero));

	if (m_HeroActors.Contains(hero) != true)
	{
		m_HeroActors.Emplace(hero);
	}
}

/*

*/
AHeroActCharacter* UPSActorManager::GetControlHeroActor()
{
	if (m_ControlHeroActor == nullptr && m_HeroActors.IsValidIndex(m_TapToHeroIndex)) 
	{
		m_ControlHeroActor = m_HeroActors[m_TapToHeroIndex];
	}
	return m_ControlHeroActor;
}

/*

*/
void UPSActorManager::SetControlHeroActor(AHeroActCharacter* hero)
{
	int idx = m_HeroActors.IndexOfByKey(hero);
	
	m_TapToHeroIndex = idx;
	m_ControlHeroActor = hero;
}

/*

*/
AHeroActCharacter* UPSActorManager::GetHeroActor(int index)
{
	return m_HeroActors.IsValidIndex(index) ? m_HeroActors[index] : nullptr;
}

/*

*/
AHeroActCharacter* UPSActorManager::GetTapToHeroActor()
{
	m_TapToHeroIndex++;
	if (m_TapToHeroIndex == m_HeroActors.Num())
		m_TapToHeroIndex = 0;

	return m_HeroActors.IsValidIndex(m_TapToHeroIndex) ? m_HeroActors[m_TapToHeroIndex] : nullptr;
}

/*

*/
//void UPSActorManager::SetTapAndControlHeroActor() 
//{
//	m_ControlHeroActor = GetTapToHeroActor();
//}

/*

*/
int32 UPSActorManager::GetRandomUniqueID()
{
	int32 rUqID = 0;
	while (true)
	{
		rUqID = FMath::RandRange(0, 1000000000);
		if (!m_TotalUniqueID.Contains(rUqID)) break;
	}
	return rUqID;
}

void UPSActorManager::GiveToUniqueID(ACoreActCharacter* character)
{
	int32 uqID = GetRandomUniqueID();
		
	m_TotalUniqueID.Emplace(uqID);

	character->SetUniqueID(uqID);

	//sUE_LOG(LogClass, Log, TEXT("rUqID %d"), uqID);

}





