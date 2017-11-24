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
	if (m_InRangeSightActs.Find(character) > -1) return;					// �̹� �þ߿� üũ �� ��ü���
	if (m_MineCharacter->GetUniqueID() == character->GetUniqueID()) return; //  ���� Ÿ�ٵ� ��ü�� �ƴ϶��
	
	
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
���� ����� �ִ���
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
			// ���ݰŸ� �ȿ� ������ . 
			// Ÿ�� �� ���̿� ��ְ� �ִ��� Ȥ�� ���� �ȿ� �ִ���
			if (m_MineCharacter->IsInSight(current) && m_MineCharacter->IsInAngle(current, 160.f))
			{
				this->m_InRangeAttackActs.Emplace(current);
			}
		}
	}

	return this->m_InRangeAttackActs.Num() > 0 ? true : false;
}

/*
���� �þ� �ȿ� �Ķ���ͷ� �Ѱܿ� ĳ���Ͱ� �ִ��� Ȯ��
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
���� ª�� �Ÿ� ���� ã�� - �˰��� �����ʿ�
*/
ACoreActCharacter* UCoreActSightSphereComponent::GetNearCharacter()
{
	// ��ü�� ������.
	if (m_MineCharacter == nullptr) return nullptr;

	// �þ߿� ��ü ������ 
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