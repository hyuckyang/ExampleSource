// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Common/PSDataSchema.h"
#include "Core/Act/CoreActState.h"
#include "CoreActCharacter.generated.h"

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

public:
	
	ACoreActCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 유니크 아이디 
	void  SetUniqueID(int32 uqID) { m_UniqueID = uqID; }
	int32 GetUniqueID() { return m_UniqueID; }


	// 상태 추가
	virtual void AddState(eStateID stateID, UCoreActState* state);

	// 상태 변경
	virtual void ChangeState(eStateID stateID, void* arg1 = nullptr, void* arg2 = nullptr);
	
	// 상태 찾기
	UCoreActState* FindState(eStateID stateID);

	// 이동 함수 - 네비게이션을 이용
	void OnUpdateToLocateWithNavi(FVector locate);
	
	// 회전 함수
	void OnUpdateToRocate(float rotateSpeed = 0.f);
	
	// 전방 타겟 각도 범위 체크
	bool IsInAngle(AActor* target, float angle);

	// 전방 타넷 시야 체크
	bool IsInSight(AActor* actors);

	// 팀 설정
	void SetTeamID(eTeamID team) { this->m_TeamID = team; }

	// 현재 타겟이 적인지 아닌지.
	bool IsEnermy(ACoreActCharacter* other) { return other->m_TeamID != this->m_TeamID ? true : false; }

	//
	//const USkeletalMeshSocket* GetMeshHudSocket() { return m_SKHudSocket; }
	bool GetHudSocketLoaction(FVector& locate);


	// 도착해야 할 백터
	//void SetTargetLocate(FVector locate) { this->m_TargetLocate = locate; }
	//FVector GetTargetLocate() { return this->m_TargetLocate; }

	//// 다시 돌아갈 백터
	//void SetReturnLocate(FVector locate) { this->m_ReturnLocate = locate; }
	//FVector GetReturnLocate() { return this->m_ReturnLocate; }

	// 기타 값 가져오기
	UFUNCTION(BlueprintCallable, Category = "Core | Character")
	eStateID GetCurrentStateID() { return this->m_CurState != nullptr ? this->m_CurState->GetStateID() : eStateID::NONE; }

	UFUNCTION(BlueprintCallable, Category = "Core | Character")
	eTeamID  GetCurrentTeamID() { return this->m_TeamID; }

	UPROPERTY(EditAnywhere)
	ACoreActSight* m_Sight;

	// 인지거리
	UPROPERTY(EditAnywhere)
	float m_SightDist = 0.f;

	// 공격거리
	UPROPERTY(EditAnywhere)
	float m_AttackDist = 0.f;

	// 타겟까지 얼마만큼 갈 것인지.
	/*UPROPERTY(EditAnywhere)
	float m_ReturnDist = 0.f;*/

	// 
	void  SetMoveForward(float value) { this->m_MoveForward = value; }
	void  SetMoveRight(float value) { this->m_MoveRight = value; }
	//
	
	UFUNCTION(BlueprintCallable, Category = "Core | Character")
	float GetMoveForward() { return this->m_MoveForward; }

	UFUNCTION(BlueprintCallable, Category = "Core | Character")
	float GetMoveRight() { return this->m_MoveRight; }

	// Test
	UFUNCTION(BlueprintCallable, Category = "Core | Character")
	void OnTickBPGetActorLocation(FVector vec3);

protected:
	USkeletalMeshComponent*			m_SKMesh;
	//const USkeletalMeshSocket*		m_SKHudSocket;

	UCoreActState*					m_CurState;
	TMap<eStateID, UCoreActState*>	m_StateMap;

	eTeamID							m_TeamID = eTeamID::NONE;

	// GameInstance;
	UPSGameInstance*				m_PSGameInstance;
	UPSActorManager*				m_ActorManager;

	// Collistion Param
	FCollisionQueryParams			params;

	int32							m_UniqueID = 0;

	// 
	float							m_MoveForward = 0.f;
	float							m_MoveRight = 0.f;;

	// Test
	FVector							m_BPActorLocation = FVector::ZeroVector;

};
