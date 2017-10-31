// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeroGunWeapon.generated.h"

class USkeletalMeshComponent;
class AHeroGunProjectile;

UCLASS()
class UE4PS_API AHeroGunWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	AHeroGunWeapon();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void OnFire();

protected:

	USkeletalMeshComponent* m_SKMesh;

};
