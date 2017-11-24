// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreActSightSphereComponent.h"

UCoreActSightSphereComponent::UCoreActSightSphereComponent() : Super()
{
	OnComponentBeginOverlap.AddDynamic(this, &UCoreActSightSphereComponent::InSightColliderBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UCoreActSightSphereComponent::InSightColliderEndOverlap);
}


void UCoreActSightSphereComponent::BeginPlay()
{
	Super::BeginPlay();

	/*m_InRangeSightActs.AddUninitialized(m_InRangeSightActs.Max());
	m_InRangeAttackActs.AddUninitialized(m_InRangeAttackActs.Max());*/
}


/*

*/
void UCoreActSightSphereComponent::InSightColliderBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor,
								   UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweeppResult)
{
	if (m_MineCharacter == nullptr) return;

	ACoreActCharacter* character = Cast<ACoreActCharacter>(otherActor);

	if (character == nullptr) return;
	if (m_InRangeSightActs.Find(character) > -1) return;					// 이미 시야에 체크 된 객체라면
	if (m_MineCharacter->GetUniqueID() == character->GetUniqueID()) return; //  현태 타겟된 객체가 아니라면
	
	
	m_InRangeSightActs.Emplace(character);
	// 
	// UE_LOG(LogClass, Log, TEXT("Begin Overlap"));
	// UE_LOG(LogClass, Log, TEXT("InSightColliderBeginOverlap"));
}

/*
*/
void UCoreActSightSphereComponent::InSightColliderEndOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor,
								   UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	if (m_MineCharacter == nullptr) return;

	ACoreActCharacter* character = Cast<ACoreActCharacter>(otherActor);
	if (character == nullptr) return;
	
	int32 idx = 0;
	if (m_InRangeSightActs.Find(character, idx) == false) return;
		
	m_InRangeSightActs.RemoveAt(idx);
	//UE_LOG(LogClass, Log, TEXT("InSightColliderEndOverlap"));
}


/*

*/
void UCoreActSightSphereComponent::SetCharacter(ACoreActCharacter* character)
{
	SetSphereRadius(character->m_SightDist); 
	m_MineCharacter = character;

	/*OnComponentBeginOverlap.AddDynamic(this, &UCoreActSightSphereComponent::InSightColliderBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UCoreActSightSphereComponent::InSightColliderEndOverlap);*/
}

/*
공격 대상이 있는지
*/
bool UCoreActSightSphereComponent::IsAttackCharacter()
{
	return false;

	if (m_InRangeSightActs.Num() == 0) return false;

	//
	m_InRangeAttackActs.Empty();

	for (int loop = 0, max = m_InRangeSightActs.Num(); loop < max; ++loop)
	{
		ACoreActCharacter* current = m_InRangeSightActs[loop];

		float dist = FVector::Distance(m_MineCharacter->GetActorLocation(), current->GetActorLocation());
		if (m_MineCharacter->m_AttackDist > dist)
		{
			// 공격거리 안에 들어오면 . 
			// 타겟 과 사이에 장애가 있는지 혹은 각도 안에 있는지
			if (m_MineCharacter->IsInSight(current) && m_MineCharacter->IsInAngle(current, 160.f))
			{
				this->m_InRangeAttackActs.Emplace(current);
			}
		}
	}

	return this->m_InRangeAttackActs.Num() > 0 ? true : false;
}

/*
현재 시야 안에 파라미터로 넘겨온 캐릭터가 있는지 확인
*/
bool UCoreActSightSphereComponent::IsInSightToCharacter(ACoreActCharacter* act)
{
	bool checkCore = m_InRangeSightActs.ContainsByPredicate([act](ACoreActCharacter* ele)
	{
		return (ele->GetUniqueID() == act->GetUniqueID());
	});
	return checkCore;
}

/*
가장 짧은 거리 액터 찾기 - 알고리즘 개선필요
*/
ACoreActCharacter* UCoreActSightSphereComponent::GetNearCharacter()
{
	// 객체가 없으면.
	if (m_MineCharacter == nullptr) return nullptr;

	// 시야에 객체 없으면 
	if (m_InRangeSightActs.Num() == 0)  return nullptr;

	ACoreActCharacter* current = nullptr;
	float nearDist = m_MineCharacter->m_SightDist;
	for (int loop = 0, max = m_InRangeSightActs.Num(); loop < max; ++loop)
	{
		float dist = FVector::Distance(m_MineCharacter->GetActorLocation(), m_InRangeSightActs[loop]->GetActorLocation());
		if (nearDist > dist) 
		{
			nearDist = dist;
			current = m_InRangeSightActs[loop];
		}
	}
	return current;
}