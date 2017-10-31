// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HeroGunProjectile.generated.h"

/*
 **
 */
UCLASS()
class UE4PS_API AHeroGunProjectile : public AActor
{
	GENERATED_BODY()

public:
	AHeroGunProjectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetProjectileVelocity(const FVector& velocityValue);

protected:

	UProjectileMovementComponent*	m_ProjectileMoveComp;
	USphereComponent*				m_SphereCollision;

	FVector							m_ShootVelocity;

};