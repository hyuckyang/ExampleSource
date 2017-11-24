// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreActSight.h"
#include "Core/Act/CoreActCharacter.h"


ACoreActSight::ACoreActSight(/*const class FObjectInitializer& initializer*/) /*: Super(initializer)*/ : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));

	//m_CollierSight = CreateDefaultSubobject<USphereComponent>(TEXT("Collider Sight"));
	//m_CollierSight->SetSphereRadius(1.f);
	//m_CollierSight->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	//// m_CollierSight->bGenerateOverlapEvents = true; // 충돌처리 True

	//m_CollierSight->OnComponentBeginOverlap.AddDynamic(this, &ACoreActSight::OnInColliderBeginOverlap);
	//m_CollierSight->OnComponentEndOverlap.AddDynamic(this, &ACoreActSight::OnInColliderEndOverlap);
	//
	
}

void ACoreActSight::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void ACoreActSight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoreActSight::SetCharacter(ACoreActCharacter* character)
{
	this->m_MineCharacter = character;
	// 설정된 인지거리에 따른 Sphere 크기를 설정함
	this->m_CollierSight->SetSphereRadius(this->m_MineCharacter->m_SightDist);
	
	//
	//this->m_CollierSight->IgnoreActorWhenMoving
}

/*
공격 대상이 있는지
*/
bool ACoreActSight::IsAttackCharacter()
{
	// 시야에 없으면..
	//m_InRangeSightActs.
	//
	try
	{
		if (this->m_InRangeSightActs.Num() == 0) return false;
	}
	catch (const std::exception&)
	{
		return false;
	}
	
	//
	this->m_InRangeAttackActs.Empty();

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
				this->m_InRangeAttackActs.Add(current);
			}
		}
	}
	
	return this->m_InRangeAttackActs.Num() > 0 ? true : false;
}

/*
가장 짧은 거리 액터 찾기 - 알고리즘 개선필요
*/
ACoreActCharacter* ACoreActSight::GetNearCharacter() 
{
	// 객체가 없으면.
	if (m_MineCharacter == nullptr) return nullptr;

	// 시야에 객체 없으면 
	if (m_InRangeSightActs.Num() == 0) return nullptr;
	
	ACoreActCharacter* current = nullptr;
	//
	float nearDist = m_MineCharacter->m_SightDist;
	//
	for (int loop = 0, max = m_InRangeSightActs.Num(); loop < max; ++loop)
	{
		float dist = FVector::Distance(m_MineCharacter->GetActorLocation(), m_InRangeSightActs[loop]->GetActorLocation());
		if (nearDist > dist) {
			nearDist = dist;
			current = m_InRangeSightActs[loop];
		}
	}
	//
	return current;
}

/*

*/
void ACoreActSight::OnInColliderBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, 
					UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweeppResult)
{

	if (m_MineCharacter == nullptr) return;

	ACoreActCharacter* character = Cast<ACoreActCharacter>(otherActor);
	if (character == nullptr) return;
	

	//  
	if (m_MineCharacter->GetUniqueID() == character->GetUniqueID()) return;

	if (m_InRangeSightActs.Find(character) > -1) return;
	//

	m_InRangeSightActs.Add(character);

	/*if (m_MineCharacter == nullptr) 
	{
		UE_LOG(LogClass, Log, TEXT("m_InRangeSightActs add %s -- mainCharacter nullptr  "), *(character->GetName())); return;
	}
	UE_LOG(LogClass, Log, TEXT("m_InRangeSightActs add %s -- mainCharacter - %s "), *(character->GetName()), *(m_MineCharacter->GetName()));*/
}

/*
*/
void ACoreActSight::OnInColliderEndOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor,
					UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	if (m_MineCharacter == nullptr) return ;

	ACoreActCharacter* character = Cast<ACoreActCharacter>(otherActor);
	if (character == nullptr) return;
	//
	int32 idx = 0;
	if (m_InRangeSightActs.Find(character, idx) == false) return;
	//
	m_InRangeSightActs.RemoveAt(idx);
}

/*
 현재 시야 안에 파라미터로 넘겨온 캐릭터가 있는지 확인
*/
bool ACoreActSight::IsInSightToCharacter(ACoreActCharacter* act)
{
	bool checkCore =  m_InRangeSightActs.ContainsByPredicate([act](ACoreActCharacter* ele)
	{
		return (ele->GetUniqueID() == act->GetUniqueID());
	});
	
	return checkCore;
}