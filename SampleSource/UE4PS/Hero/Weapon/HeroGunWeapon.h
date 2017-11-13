// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	void OnFire();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect | Particle")
	UParticleSystem*			m_MuzzleParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect | Sound")
	class USoundcue*				m_MuzzleFireSound;

protected:

	class USkeletalMeshComponent*	m_SKMesh;
	class ACoreActCharacter*		m_MineCoreAct;


};
