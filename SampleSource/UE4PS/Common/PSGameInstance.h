// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PSGameInstance.generated.h"

class UPSActorManager;
class UPSWidgetManager;
class UPSDataManager;
class APSFieldRobotCreatePoint;
class APSFixedGoalToProtect;
class ACoreCameraControl;
/**
 * 
 */
UCLASS()
class UE4PS_API UPSGameInstance : public UGameInstance
{
	GENERATED_BODY()


	UPSWidgetManager*	m_WidgetManager = nullptr;
	UPSActorManager*	m_ActorManager	= nullptr;
	UPSDataManager*		m_DataManager	= nullptr;

	// Field Control Actor ( 카메라 컨트롤러 상속받은 객체. )
	ACoreCameraControl* m_CameraControlActor;

	// 로봇( 적 ) 을 생성하는 타겟 포인트는 별도의 매니저 없이 간단히 리스트로 관리합니다. ( 때마다 게임모드에서 호출할 거라.. )
	TArray<APSFieldRobotCreatePoint*> m_FieldCreatePoints;
	//
	APSFixedGoalToProtect* m_GoalActor;
public:

	virtual void Init() override;
	virtual void StartGameInstance() override;

	/*
	Manager Func
	*/
	void CreateManagerObeject();

	UPSWidgetManager*	GetWidgetManager()	{ return this->m_WidgetManager; }
	UPSActorManager*	GetActorManager()	{ return this->m_ActorManager; }
	UPSDataManager*		GetDataManager()	{ return this->m_DataManager; }

	void SetCameraControlActor(ACoreCameraControl*  control) { this->m_CameraControlActor = control; }
	ACoreCameraControl* GetCamaraControlActor() { return this->m_CameraControlActor; }

	/*
	Robot Create Func;
	*/
	void AddToFieldCreatePoint(APSFieldRobotCreatePoint* point) { if (!m_FieldCreatePoints.Contains(point)) m_FieldCreatePoints.Emplace(point); }
	void OnWaveCreateRobots(int waveNumber);

	/*
	Goal Func
	*/ 
	void SetToGoalActor(APSFixedGoalToProtect* goalActor) { this->m_GoalActor = goalActor; }

	UFUNCTION(BlueprintCallable, Category = "Robot | AI")
	APSFixedGoalToProtect* GetGoalActor() { return m_GoalActor; }


};
