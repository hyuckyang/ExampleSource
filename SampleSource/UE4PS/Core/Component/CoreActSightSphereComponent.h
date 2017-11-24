// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Act/CoreActCharacter.h"
#include "Components/SphereComponent.h"
#include "CoreActSightSphereComponent.generated.h"

/**
 * 
 */
UCLASS()
class UE4PS_API UCoreActSightSphereComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:

	UCoreActSightSphereComponent();

	virtual void BeginPlay();
	
	UFUNCTION()
	void InSightColliderBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
									 int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweeppResult);

	UFUNCTION()
	void InSightColliderEndOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
								   int32 otherBodyIndex);

	
	// Search And Add
	bool IsAttackCharacter();
	bool IsInSightToCharacter(ACoreActCharacter* character);
	ACoreActCharacter* GetNearCharacter();
	TArray<ACoreActCharacter*> GetPossibleAttackActList() { return m_InRangeAttackActs; }


	/*
	캐릭터 및 구 셋팅
	*/
	void SetCharacter(ACoreActCharacter* character);
	void SetSightDistance(float dist) { SetSphereRadius(dist); }

private:

	ACoreActCharacter*			m_MineCharacter;	 // 타겟 객체

	UPROPERTY()
	TArray<ACoreActCharacter*>	m_InRangeSightActs;  // 시야에 들어온 객체
	UPROPERTY()
	TArray<ACoreActCharacter*>	m_InRangeAttackActs; // 공격 가능한 객체

};
