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
	this->m_CollierSight->bGenerateOverlapEvents = true; // �浹ó�� True

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
	// ������ �����Ÿ��� ���� Sphere ũ�⸦ ������
	this->m_CollierSight->SetSphereRadius(this->m_MineCharacter->m_SightDist);
}

/*
���� ����� �ִ���
*/
bool ACoreActSight::IsAttackCharacter()
{
	// �þ߿� ������..
	if (this->m_InRangeSightActs.Num() == 0) return false;
	//
	this->m_InRangeAttackActs.Empty();

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
				this->m_InRangeAttackActs.Add(current);
			}
		}
	}
	
	return this->m_InRangeAttackActs.Num() > 0 ? true : false;
}

/*
���� ª�� �Ÿ� ���� ã�� - �˰��� �����ʿ�
*/
ACoreActCharacter* ACoreActSight::GetNearCharacter() 
{
	// �þ߿� ��ü ������ 
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