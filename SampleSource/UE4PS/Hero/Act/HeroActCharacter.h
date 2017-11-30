// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/Material.h"
#include "Common/PSDataSchema.h"
#include "Hero/Act/HeroActState.h"
#include "Hero/AI/HeroAIController.h"
#include "Core/Act/CoreActCharacter.h"
#include "HeroActCharacter.generated.h"

DECLARE_DELEGATE_OneParam(SwitcherWeaponTriggerDelegate, eWeaponTriggerID);
DECLARE_DELEGATE_OneParam(SelectCharacterDelegate, bool);

class AHeroGunWeapon;
class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class UE4PS_API AHeroActCharacter : public ACoreActCharacter
{
	GENERATED_BODY()

	SwitcherWeaponTriggerDelegate	m_switcherWTriggerDele;
	SelectCharacterDelegate			m_selectCharacterDele;

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
	void OnFire(bool bCanFire = true);
	eWeaponTriggerID GetWeaponTriggerID();
	void OnWeaponTriggerSwitcher();
	
	//
	template<typename T>
	void SwitcherWTriggerFuncBind(UObject* obj, void (T::*funcPoint)(eWeaponTriggerID)) { m_switcherWTriggerDele.BindUObject(Cast<T>(obj), funcPoint); }

	template<typename T>
	void SelectCharacterFuncBind(UObject* obj, void (T::*funcPoint)(bool)) { m_selectCharacterDele.BindUObject(Cast<T>(obj), funcPoint); }

	// AI
	AHeroAIController*  GetHeroAIContol() { return this->m_HAIController; }

public :
	UPROPERTY(EditDefaultsOnly, Category = "Hero | Montage")
	class UAnimMontage*		m_HeroRifleOneShootMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Hero | AI")
	class UBehaviorTree*	m_HeroAIBT;
	
protected:

	AHeroAIController*		m_HAIController = nullptr;

	FString					m_HeroName;
	eHeorControlID			m_ControlID;
	UStaticMeshComponent*	m_PointSMMesh;

	AHeroGunWeapon*			m_GunWeapon;


	//
	//UDecalComponent* m_DecalToTarget;
	//UDecalComponent* m_CursurToDecal;*/
	

	
	
};
