// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroGunProjectile.h"
#include "Core/Act/CoreActCharacter.h"


/*
 참조 - http://cafe.naver.com/unrealenginekr/85 
*/
AHeroGunProjectile::AHeroGunProjectile()
{
 	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));

	m_SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collider Sight"));
	m_SphereCollision->SetSphereRadius(1.f);
	//m_SphereCollision->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	m_SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	m_SphereCollision->bGenerateOverlapEvents = true; // 충돌처리 True
	m_SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AHeroGunProjectile::OnInColliderBeginOverlap);

	RootComponent = m_SphereCollision;
}


void AHeroGunProjectile::BeginPlay()
{
	Super::BeginPlay();	

	SetLifeSpan(3.f);

	//UE_LOG(LogClass, Log, TEXT("BeginPlay"));
}

void AHeroGunProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ??
	FVector fwVec3 = GetActorLocation() + GetActorForwardVector();
	SetActorRelativeLocation(fwVec3);
}

void AHeroGunProjectile::SetCoreCharcter(ACoreActCharacter* coreCharcter)
{
	m_MineCoreAct = coreCharcter;
}

void AHeroGunProjectile::SetProjectileVelocity(const FVector& velocityValue)
{
	m_ShootVelocity = velocityValue;
}



void AHeroGunProjectile::OnInColliderBeginOverlap(class UPrimitiveComponent* overlappedComp, class AActor* otherActor, class UPrimitiveComponent* otherComp,
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweeppResult)
{
	if (m_MineCoreAct == nullptr) { return; }

	if (m_MineCoreAct !=nullptr && otherActor != nullptr)
	{
		ACoreActCharacter* coreAct = Cast<ACoreActCharacter>(otherActor);

		if (coreAct != nullptr) 
		{
			if (m_MineCoreAct->IsEnermy(coreAct)) 
			{
				coreAct->ReceivedAttackDamage(m_MineCoreAct->m_PointMeleeAttack);
			}
		}
	}

	Destroy();
}
