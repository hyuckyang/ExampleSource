// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common/PSDataSchema.h"
#include "Core/Act/CoreActCharacter.h"
#include "HeroGunWeapon.generated.h"


//class USkeletalMeshComponent;
class AHeroGunProjectile;

UCLASS()
class UE4PS_API AHeroGunWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	AHeroGunWeapon();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetCoreCharcter(ACoreActCharacter* coreCharcter) { m_MineCoreAct = coreCharcter; }
	void OnFire(bool Canfire = true);
	
	void CanShootDelay();
	void ShootProjectile();

	eWeaponTriggerID GetWTriggerID() { return m_TriggerID; }
	void SetTriggerSwitch();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect | Particle")
	UParticleSystem*				m_MuzzleParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect | Sound")
	class USoundcue*				m_MuzzleFireSound;

protected:

	class USkeletalMeshComponent*	m_SKMesh;
	class ACoreActCharacter*		m_MineCoreAct;
	//
	eWeaponTriggerID				m_TriggerID				= eWeaponTriggerID::SEMIAUTO;

	FTimerHandle					m_TimeHandleFireDelay;
	float							m_TimeFireDelaySec		= 0.08f;
	bool							m_bFirePossible			= true;
	bool							m_bCanFire				= false;

	int32							m_BusrtValue			= 3;
	int32							m_BurstCount			= 0;
};
