// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroGunProjectile.h"


/*
 ÂüÁ¶ - http://cafe.naver.com/unrealenginekr/85 
*/
AHeroGunProjectile::AHeroGunProjectile()
{
 	PrimaryActorTick.bCanEverTick = true;

	//m_ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	////m_ProjectileMoveComp->UpdatedComponent = RootComponent;
	//m_ProjectileMoveComp->InitialSpeed = 1000.0f;
	//m_ProjectileMoveComp->MaxSpeed = 1000.0f;
	//m_ProjectileMoveComp->bRotationFollowsVelocity = true;
	//m_ProjectileMoveComp->ProjectileGravityScale = 0.f;

	//m_ProjectileMoveComp->Velocity = GetVelocity() * 500.f;

	m_SphereCollision = FindComponentByClass<USphereComponent>();
	if (m_SphereCollision == nullptr) { UE_LOG(LogClass, Log, TEXT("USphereComponent nullptr")); }
	else { UE_LOG(LogClass, Log, TEXT("USphereComponent not nullptr")); }
	//m_ProjectileMoveComp = 
	
	
}

//ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
//ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
//ProjectileMesh->SetupAttachment(RootComponent);
//ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
//ProjectileMesh->OnComponentHit.AddDynamic(this, &ATweenShootSampleProjectile::OnHit);		// set up a notification for when this component hits something
//RootComponent = ProjectileMesh;
//
//// Use a ProjectileMovementComponent to govern this projectile's movement
//ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
//ProjectileMovement->UpdatedComponent = ProjectileMesh;
//ProjectileMovement->InitialSpeed = 3000.f;
//ProjectileMovement->MaxSpeed = 3000.f;
//ProjectileMovement->bRotationFollowsVelocity = true;
//ProjectileMovement->bShouldBounce = false;
//ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity
//
//												  // Die after 3 seconds by default
//InitialLifeSpan = 3.0f;


void AHeroGunProjectile::BeginPlay()
{
	Super::BeginPlay();	

	/*m_SphereCollision = FindComponentByClass<USphereComponent>();
	if (m_SphereCollision == nullptr) return;


	m_ProjectileMoveComp = FindComponentByClass<UProjectileMovementComponent>();
	if (m_ProjectileMoveComp == nullptr) return;*/

	//m_ProjectileMoveComp->Velocity = GetVelocity() * 1000.0f;

	m_SphereCollision = FindComponentByClass<USphereComponent>();
	if (m_SphereCollision == nullptr) return;

	m_ProjectileMoveComp = FindComponentByClass<UProjectileMovementComponent>();
	if (m_ProjectileMoveComp == nullptr) return;

	//m_ProjectileMoveComp->SetUpdatedComponent(m_SphereCollision);
	//m_ProjectileMoveComp->Velocity = m_ShootVelocity * m_ProjectileMoveComp->InitialSpeed;

}

void AHeroGunProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroGunProjectile::SetProjectileVelocity(const FVector& velocityValue)
{
	m_ShootVelocity = velocityValue;

	m_ProjectileMoveComp->Velocity = m_ShootVelocity * m_ProjectileMoveComp->InitialSpeed;
	
	//SetActorRotation(velocityValue);
	


}

