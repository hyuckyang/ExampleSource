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
	m_SphereCollision->bGenerateOverlapEvents = true; // 충돌처리 True

	m_SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AHeroGunProjectile::OnInColliderBeginOverlap);

	RootComponent = m_SphereCollision;
}


void AHeroGunProjectile::BeginPlay()
{
	Super::BeginPlay();	

	SetLifeSpan(3.f);
}

void AHeroGunProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ??
	FVector fwVec3 = GetActorLocation() + GetActorForwardVector();
	SetActorRelativeLocation(fwVec3);
}

void AHeroGunProjectile::SetProjectileVelocity(const FVector& velocityValue)
{
	m_ShootVelocity = velocityValue;
	
	//if (m_ProjectileMoveComp == nullptr) m_ProjectileMoveComp = FindComponentByClass<UProjectileMovementComponent>();
	////m_ProjectileMoveComp->Velocity = m_ShootVelocity * m_ProjectileMoveComp->InitialSpeed;
	//m_ProjectileMoveComp->SetVelocityInLocalSpace(m_ShootVelocity * m_ProjectileMoveComp->InitialSpeed);

}



void AHeroGunProjectile::OnInColliderBeginOverlap(class UPrimitiveComponent* overlappedComp, class AActor* otherActor, class UPrimitiveComponent* otherComp,
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweeppResult)
{
	if (m_MineCoreAct && otherActor )
	{
		ACoreActCharacter* coreAct = Cast<ACoreActCharacter>(otherActor);
		if (coreAct != nullptr) 
		{
			if (m_MineCoreAct->IsEnermy(coreAct)) 
			{
				coreAct->ReceivedAttackDamage(1);

				coreAct->OnDeath();
			}
		}
	}

	Destroy();
}
