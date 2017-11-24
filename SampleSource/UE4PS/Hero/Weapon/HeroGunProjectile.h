// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Core/Act/CoreActCharacter.h"
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

	void SetCoreCharcter(ACoreActCharacter* coreCharcter);
	void SetProjectileVelocity(const FVector& velocityValue);
	
	UFUNCTION()
	void OnInColliderBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
									int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweeppResult);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent*				m_SphereCollision;

	
protected:

	UProjectileMovementComponent*	m_ProjectileMoveComp;
	FVector							m_ShootVelocity;

	ACoreActCharacter*				m_MineCoreAct;
};