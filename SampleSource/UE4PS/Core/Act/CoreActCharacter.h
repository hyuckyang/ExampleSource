// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Common/PSDataSchema.h"
#include "Core/Act/CoreActState.h"
#include "CoreActCharacter.generated.h"

DECLARE_DELEGATE_OneParam(ReceiveDamageDelegate, int32);

class UWidgetComponent;
class UCoreActSightSphereComponent;
class UCharacterMovementComponent;
class USkeletalMeshComponent;
class UPSGameInstance;
class UPSActorManager;
class ACoreActSight;

/**
 *
 */
UCLASS()
class UE4PS_API ACoreActCharacter : public ACharacter
{
	GENERATED_BODY()

	ReceiveDamageDelegate m_receiveDamageDele;

/*
 * ���� ���� �Լ� �� ���� ��
 */
protected:

	// TMap<eStateKindOfID, UCoreActState*>	m_CurStateList;

	UPROPERTY()
	UCoreActState*							m_CurState;

	UPROPERTY()
	TMap<eStateID, UCoreActState*>			m_StateMap;

public:

	/*virtual void AddState(eStateKindOfID stateKindOfID, eStateID stateID, UCoreActState* state) {};
	virtual void ChangeState(eStateKindOfID stateKindOfID, eStateID stateID, void* arg1 = nullptr, void* arg2 = nullptr) {};*/

	// ���� �߰�
	virtual void AddState(eStateID stateID, UCoreActState* state);

	// ���� ����
	virtual void ChangeState(eStateID stateID, void* arg1 = nullptr, void* arg2 = nullptr);

	// ���� ã��
	UCoreActState* FindState(eStateID stateID);

	// ��Ÿ �� ��������
	UFUNCTION(BlueprintCallable, Category = "Core | Character")
	eStateID GetCurrentStateID() { return this->m_CurState != nullptr ? this->m_CurState->GetStateID() : eStateID::NONE; }


/*
*/
public:
	
	ACoreActCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ����ũ ���̵� 
	void  SetUniqueID(int32 uqID) { m_UniqueID = uqID; }
	int32 GetUniqueID() { return m_UniqueID; }

	void SetLocalData();

	// �̵� �Լ� - �׺���̼��� �̿�
	void OnUpdateToLocateWithNavi(FVector locate);
	
	// ȸ�� �Լ�
	void OnUpdateToRocate(float rotateSpeed = 0.f);
	
	// ���� Ÿ�� ���� ���� üũ
	bool IsInAngle(AActor* target, float angle);

	// ���� Ÿ�� �þ� üũ
	bool IsInSight(AActor* actors);

	// �� ����
	void SetTeamID(eActorTypeID team) { this->m_ActorTypeID = team; }

	// ���� Ÿ���� ������ �ƴ���.
	bool IsEnermy(ACoreActCharacter* other) { return other->m_TeamID != this->m_TeamID ? true : false; }

	//
	bool GetHudSocketLoaction(FVector& locate);

	//
	virtual void SetSelected(bool bVisible) {}
	virtual void ReceivedAttackDamage(int32 damageValue) { m_receiveDamageDele.ExecuteIfBound(damageValue); }

	/*void ReceiveDamageFuncBind(UObject* obj, void (ACoreActCharacter::*funcPoint)(int32)) { m_receiveDamageDele.BindUObject(obj, funcPoint); }*/
	template<typename T>
	void ReceiveDamageFuncBind(UObject* obj, void (T::*funcPoint)(int32)) { m_receiveDamageDele.BindUObject(Cast<T>(obj), funcPoint); }


	UFUNCTION(BlueprintCallable, Category = "Core | Character")
	eTeamID  GetCurrentTeamID() { return this->m_TeamID; }

	UFUNCTION(BlueprintCallable, Category = "Core | Character")
	eActorTypeID  GetCurrentActorTypeID() { return this->m_ActorTypeID; }

	void  SetMoveForward(float value) { m_MoveDir.X = value; }
	void  SetMoveRight(float value) { m_MoveDir.Y = value; }
	
	FVector2D GetMoveDir() { return m_MoveDir; }

	UFUNCTION(BlueprintCallable, Category = "Core | Character")
	float GetMoveForward() { return m_MoveDir.X; }

	UFUNCTION(BlueprintCallable, Category = "Core | Character")
	float GetMoveRight() { return m_MoveDir.Y; }


	void SetHeadBar();
	//
	virtual void OnDeath(float delayExploer = 0.f) {}

	void OnDeathToRagDollActive(FVector bounceDir = FVector::ZeroVector);
	void OnDeathToParticle();

	
public:

	//
	int32 m_CurrentHP			= 0;
	int32 m_PointHealth			= 0; // 
	int32 m_PointSpeed			= 0; //
	int32 m_PointMeleeAttack	= 0; //

	/*UPROPERTY(EditAnywhere)
	ACoreActSight* m_Sight;*/

	UPROPERTY(EditAnywhere)
	UCoreActSightSphereComponent* m_SightComp;

	// �����Ÿ�
	UPROPERTY(EditAnywhere)
	float m_SightDist = 0.f;

	// ���ݰŸ�
	UPROPERTY(EditAnywhere)
	float m_AttackDist = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Death | Particle")
	UParticleSystem*			m_DeathParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Death | Sound")
	class USoundcue*			m_DeathSoundCue;



protected:
	USkeletalMeshComponent*					m_SKMesh;
	UCharacterMovementComponent*			m_CHMoveComp;
	UWidgetComponent*						m_HeadBar; // * ���� - http://cafe.naver.com/unrealenginekr/14835


	eActorTypeID							m_ActorTypeID = eActorTypeID::NONE;
	eTeamID									m_TeamID = eTeamID::NONE;

	// GameInstance;
	UPSGameInstance*						m_PSGameInstance;
	UPSActorManager*						m_ActorManager;

	// Collistion Param
	FCollisionQueryParams					params;

	int32									m_UniqueID = 0;

	// 
	float									m_MoveForward = 0.f;
	float									m_MoveRight = 0.f;;

	// KeyBoard 
	FVector2D								m_MoveDir = FVector2D::ZeroVector;

};
