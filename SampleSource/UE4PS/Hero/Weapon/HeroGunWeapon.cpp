// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroGunWeapon.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "Components/SkeletalMeshComponent.h"
#include "Hero/Weapon/HeroGunProjectile.h"


AHeroGunWeapon::AHeroGunWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHeroGunWeapon::BeginPlay()
{
	Super::BeginPlay();

	m_SKMesh = FindComponentByClass<USkeletalMeshComponent>();
}

void AHeroGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroGunWeapon::OnFire()
{
	if (m_SKMesh == nullptr) return;
	if (m_MineCoreAct == nullptr) return;

	UClass* bpGC = LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("Blueprint'/Game/A_Sample/Hero/Weapon/BP_HeroGunProjectile.BP_HeroGunProjectile_C'"));
	if (bpGC == nullptr) return;

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;
	//spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector muzzleLocate = m_SKMesh->GetSocketLocation("MuzzleFlash");
	FRotator gunRotate = GetActorRotation();

	AHeroGunProjectile* gunProjectile = 
		GetWorld()->SpawnActor<AHeroGunProjectile>(bpGC->GetDefaultObject()->GetClass(), 
			muzzleLocate, gunRotate, spawnParams);
	
	if (gunProjectile != nullptr)
		gunProjectile->SetCoreCharcter(m_MineCoreAct);

	// Effect 
	UGameplayStatics::SpawnEmitterAtLocation(this, m_MuzzleParticle, muzzleLocate, gunRotate);
	UGameplayStatics::SpawnSoundAtLocation(this, (USoundBase*)m_MuzzleFireSound, muzzleLocate);
	return;
}