// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "CoreActSight.generated.h"

class ACoreActCharacter;
/*
*
*/
UCLASS()
class UE4PS_API ACoreActSight : public AActor
{
	GENERATED_BODY()
	
public:	
	ACoreActSight();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnInColliderBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
								  int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweeppResult);

	UFUNCTION()
	void OnInColliderEndOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
								  int32 otherBodyIndex);
	//
	void SetCharacter(ACoreActCharacter* character);
	//
	void SetSightDistance(float dist) { this->m_CollierSight->SetSphereRadius(dist); }
	
	// 공격 할 캐릭터 - 검색 / 있는지 or 없는지
	bool IsAttackCharacter();
	//
	ACoreActCharacter* GetNearCharacter();


protected:

	// 에디터 에서만 참조 - BP 는 그냥 참조
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent*			m_CollierSight;

	//
	ACoreActCharacter*			m_MineCharacter;
	// 시야 안의 객체
	TArray<ACoreActCharacter*>	m_InRangeSightActs;
	// 시야 안의 공격 대상 들
	TArray<ACoreActCharacter*>	m_InRangeAttackActs;

};
