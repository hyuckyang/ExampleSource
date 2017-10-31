// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/Material.h"
#include "Common/PSDataSchema.h"
#include "Hero/Act/HeroActState.h"
#include "Core/Act/CoreActCharacter.h"
#include "HeroActCharacter.generated.h"

class AHeroGunWeapon;
class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class UE4PS_API AHeroActCharacter : public ACoreActCharacter
{
	GENERATED_BODY()
	
public:

	AHeroActCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void AddState(eStateID stateID, UCoreActState* state);
	virtual void ChangeState(eStateID stateID, void* arg1 = nullptr, void* arg2 = nullptr);

	virtual void SetSelected(bool bVisible);

	UFUNCTION(BlueprintCallable)
	eHeorControlID GetHeroControlID() { return this->m_ControlID; }
	//
	void SetHeroControlID(eHeorControlID controlID);
	

	/*
	Action_Male 을 컨텐츠를 활용하였기에 별도의 함수를 제작합니다.
	*/
	void RandomCustomizing();
	void RandomNames();

	FString GetName() { return this->m_HeroName; }

	// Weapon
	void OnFire();
	
protected:
	FString					m_HeroName;
	eHeorControlID			m_ControlID;
	UStaticMeshComponent*	m_PointSMMesh;

	AHeroGunWeapon*			m_GunWeapon;
	
	//
	//UDecalComponent* m_DecalToTarget;
	//UDecalComponent* m_CursurToDecal;*/
	

	
	
};
