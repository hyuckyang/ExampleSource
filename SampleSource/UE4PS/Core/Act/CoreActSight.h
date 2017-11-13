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
	ACoreActSight(const class FObjectInitializer& initializer);
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
	
	// ���� �� ĳ���� - �˻� / �ִ��� or ������
	bool IsAttackCharacter();
	//
	ACoreActCharacter* GetNearCharacter();

	bool IsInSightToCharacter(ACoreActCharacter* act);

	TArray<ACoreActCharacter*> GetPossibleAttackActList() { return m_InRangeAttackActs; }
protected:

	// ������ ������ ���� - BP �� �׳� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent*			m_CollierSight;

	//
	ACoreActCharacter*			m_MineCharacter;
	// �þ� ���� ��ü
	TArray<ACoreActCharacter*>	m_InRangeSightActs;
	// �þ� ���� ���� ��� ��
	TArray<ACoreActCharacter*>	m_InRangeAttackActs;

};
