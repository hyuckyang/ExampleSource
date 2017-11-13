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
	Action_Male �� �������� Ȱ���Ͽ��⿡ ������ �Լ��� �����մϴ�.
	*/
	void RandomCustomizing();
	void RandomNames();

	FString GetName() { return this->m_HeroName; }

	// Weapon
	void OnFire();

public :
	UPROPERTY(EditDefaultsOnly, Category = "Hero | Montage")
	class UAnimMontage*		m_HeroRifleOneShootMontage;
	
protected:
	FString					m_HeroName;
	eHeorControlID			m_ControlID;
	UStaticMeshComponent*	m_PointSMMesh;

	AHeroGunWeapon*			m_GunWeapon;
	
	//
	//UDecalComponent* m_DecalToTarget;
	//UDecalComponent* m_CursurToDecal;*/
	

	
	
};
