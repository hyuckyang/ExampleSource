// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreActSight.h"
#include "Core/Act/CoreActCharacter.h"


ACoreActSight::ACoreActSight()
{
	PrimaryActorTick.bCanEverTick = true;

	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));

	this->m_CollierSight = CreateDefaultSubobject<USphereComponent>(TEXT("Collider Sight"));
	this->m_CollierSight->SetSphereRadius(1.f);
	this->m_CollierSight->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	this->m_CollierSight->bGenerateOverlapEvents = true; // 충돌처리 True

	//
	this->m_CollierSight->OnComponentBeginOverlap.AddDynamic(this, &ACoreActSight::OnInColliderBeginOverlap);
	this->m_CollierSight->OnComponentEndOverlap.AddDynamic(this, &ACoreActSight::OnInColliderEndOverlap);
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
}

/*
공격 대상이 있는지
*/
bool ACoreActSight::IsAttackCharacter()
{
	// 시야에 없으면..
	if (this->m_InRangeSightActs.Num() == 0) return false;
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
	ACoreActCharacter* character = Cast<ACoreActCharacter>(otherActor);
	if (character == nullptr) return;
	//
	if (m_InRangeSightActs.Find(character) > -1) return;
	//
	m_InRangeSightActs.Add(character);
}

/*

*/
void ACoreActSight::OnInColliderEndOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor,
					UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	ACoreActCharacter* character = Cast<ACoreActCharacter>(otherActor);
	if (character == nullptr) return;
	//
	int32 idx = 0;
	if (m_InRangeSightActs.Find(character, idx) == false) return;
	//
	m_InRangeSightActs.RemoveAt(idx);
}