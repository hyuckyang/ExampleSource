// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroGunWeapon.h"
#include "Runtime/Engine/Classes/Engine/BlueprintGeneratedClass.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "Components/SkeletalMeshComponent.h"
#include "Hero/Weapon/HeroGunProjectile.h"
#include "Public/TimerManager.h"

AHeroGunWeapon::AHeroGunWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHeroGunWeapon::BeginPlay()
{
	Super::BeginPlay();

	m_SKMesh = FindComponentByClass<USkeletalMeshComponent>();

	//
	
}

void AHeroGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroGunWeapon::OnFire(bool Canfire)
{
	m_bCanFire = Canfire;

	// 이미 발사 중이면..
	if (!m_bCanFire) return;
	if (!m_bFirePossible) return;
	//

	if (m_TriggerID == eWeaponTriggerID::BURST)
	{
		m_BurstCount = 0;
	}

	m_bFirePossible = false;
	ShootProjectile();
}



void AHeroGunWeapon::CanShootDelay( )
{
	// ShootProjectile();
	// 0.08f 은 테이블로 빠져야 합니다.
	// GetWorldTimerManager().SetTimer(m_TimeHandleFireDelay, this, &AHeroGunWeapon::ShootProjectile, m_TimeFireDelaySec, false);
	
	m_TimeHandleFireDelay.Invalidate();
	GetWorldTimerManager().ClearTimer(m_TimeHandleFireDelay);

	// UE_LOG(LogClass, Log, TEXT("CanShootDelay"));

	switch (m_TriggerID)
	{
		case eWeaponTriggerID::NONE:
		case eWeaponTriggerID::SEMIAUTO: 
		{ 
			m_bCanFire = false;
			m_bFirePossible = true;

			break; 
		}
		case eWeaponTriggerID::BURST:
		{
			if (!m_bCanFire)
			{
				m_bFirePossible = true;

				return;
			}

			m_BurstCount++;

			if (m_BurstCount >= m_BusrtValue)
			{
				m_bCanFire = false;
				m_bFirePossible = true;
				return;
			}
			ShootProjectile();
			break;

		}
		case eWeaponTriggerID::FULLAUTO:
		{
			if (!m_bCanFire)
			{
				m_bFirePossible = true;

				UE_LOG(LogClass, Log, TEXT("eWeaponTriggerID::FULLAUTO:"));
				return;
			}
			ShootProjectile();
			break;
		}
	}

	
}

void AHeroGunWeapon::ShootProjectile()
{
	/*
	 *
	 */
	if (m_SKMesh == nullptr) return;
	if (m_MineCoreAct == nullptr) return;

	UClass* bpGC = LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("Blueprint'/Game/A_Sample/Hero/Weapon/BP_HeroGunProjectile.BP_HeroGunProjectile_C'"));
	if (bpGC == nullptr) return;

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;
	//spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector	muzzleLocate = m_SKMesh->GetSocketLocation("MuzzleFlash");
	FRotator gunRotate = GetActorRotation();

	AHeroGunProjectile* gunProjectile =
		GetWorld()->SpawnActor<AHeroGunProjectile>(bpGC->GetDefaultObject()->GetClass(),
			muzzleLocate, gunRotate, spawnParams);

	if (gunProjectile != nullptr)
		gunProjectile->SetCoreCharcter(m_MineCoreAct);

	// Effect 
	UGameplayStatics::SpawnEmitterAtLocation(this, m_MuzzleParticle, muzzleLocate, gunRotate);
	UGameplayStatics::SpawnSoundAtLocation(this, (USoundBase*)m_MuzzleFireSound, muzzleLocate);


	// 0.08f 은 테이블로 빠져야 합니다.
	//GetWorldTimerManager().SetTimer(m_TimeHandleAttackMontage, this, &ARobotActCharacter::PlayAttackAnimLoop, m_TimeHandleSec, true);
	GetWorldTimerManager().SetTimer(m_TimeHandleFireDelay, this, &AHeroGunWeapon::CanShootDelay, m_TimeFireDelaySec, false);
	//UE_LOG(LogClass, Log, TEXT("ShootProjectile"));
	return;
}

void AHeroGunWeapon::SetTriggerSwitch()
{
	/*uint8 cur = (uint8)(m_TriggerID);
	if (m_TriggerID  == eWeaponTriggerID::FULLAUTO)
	{
		m_TriggerID = eWeaponTriggerID::SEMIAUTO;
	}
	else 
	{
		m_TriggerID = (eWeaponTriggerID)((uint8)(cur)+1);
	}*/
	switch (m_TriggerID)
	{
		case eWeaponTriggerID::NONE:
		case eWeaponTriggerID::SEMIAUTO:
		{
			m_TriggerID = eWeaponTriggerID::BURST;
			break;
		}
		case eWeaponTriggerID::BURST:
		{
			m_TriggerID = eWeaponTriggerID::FULLAUTO;
			break;
		}
		case eWeaponTriggerID::FULLAUTO:
		{
			m_TriggerID = eWeaponTriggerID::SEMIAUTO;
			break;
		}
	}
}