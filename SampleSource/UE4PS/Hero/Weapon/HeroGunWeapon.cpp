// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroGunWeapon.h"
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

	UClass* bpGC = LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("Blueprint'/Game/A_Sample/Hero/Weapon/BP_HeroGunProjectile.BP_HeroGunProjectile_C'"));
	if (bpGC == nullptr) return;

	AHeroGunProjectile* gunProjectile = GetWorld()->SpawnActor<AHeroGunProjectile>(bpGC->GetDefaultObject()->GetClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	
	gunProjectile->SetActorLocation(m_SKMesh->GetSocketLocation("MuzzleFlash"));
	gunProjectile->SetActorRotation(GetActorRotation());

	gunProjectile->SetProjectileVelocity(GetVelocity());
	return;
}