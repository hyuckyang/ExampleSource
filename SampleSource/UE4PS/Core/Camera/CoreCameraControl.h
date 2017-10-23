// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Common/PSDataSchema.h"
#include "Camera/CameraComponent.h"
#include "CoreCameraControl.generated.h"

class UPSGameInstance;
class UPSActorManager;
class UPSWidgetManager;
	   
/**
*
*/
UCLASS()
class UE4PS_API ACoreCameraControl : public APawn
{
	GENERATED_BODY()
	
public:

	// Default Pawn 임!

	ACoreCameraControl();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 카메라 조작.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* m_pCamera;

	UPROPERTY(EditAnywhere)
	float m_fCamDistMin;

	UPROPERTY(EditAnywhere)
	float m_fCamDistMax;

	UPROPERTY(EditAnywhere)
	float m_fCamDist;

	UPROPERTY(EditAnywhere)
	float m_fCamYaw;

	UPROPERTY(EditAnywhere)
	float m_fCamPitch;

	UPROPERTY(EditAnywhere)
	bool m_bRotateCam;

	UPROPERTY(EditAnywhere)
	float m_fLocateSpeed;

	UPROPERTY(EditAnywhere)
	float m_fRotateSpeed;

	UPROPERTY(EditAnywhere)
	float m_fZoomSpeed;

	void	 InitCameraParameter();

	FVector  GetPointViewVector(float dist, float pitch, float yaw);
	FVector  GetAddVec3ToLocate(FVector vec3, float amount);
	FRotator GetIsolateYaw(FRotator rotator);
	void     OnUpdateLocateAndRotate();

	//// 입력 Action
	//virtual void InputMouseWheelUp() {};
	//virtual void InputMouseWheelDown() {};
	//virtual void InputMouseLClickPressed() {};
	//virtual void InputMouseLClickReleased() {};
	//virtual void InputMouseRClickPressed() {};
	//virtual void InputMouseRClickReleased() {};
	//virtual void InputTapClickPressed() {};
	//virtual void InputTapClickReleased() {};
	//// 입력 Axis
	//virtual void InputMouseX(float deltaTime) {};
	//virtual void InputMouseY(float deltaTime) {};
	// void OnInputKeyBoardForward(float deltaTime) { this->OnMoveForward(deltaTime); };
	//virtual void InputKeyBoardRight(float deltaTime) {};

	
	// 이동. 회전 등.
	void OnMoveForward(float amount);
	void OnMoveRight(float amount);
	void OnRotatePitch(float delta);
	void OnRotateYaw(float delte);
	void OnZoomIn();
	void OnZoomOut();
	//
	
	UCameraComponent* GetCamera() { return this->m_pCamera; }
	eCameraControlID  GetCameraControlID() { return this->m_ControlID; }
protected:
	//
	eCameraControlID	m_ControlID;
	APlayerController*  m_pController;
	UPSGameInstance*	m_PSGameInstance;
	UPSActorManager*	m_ActorManager;
	UPSWidgetManager*	m_WidgetManager;
	//
	FVector				m_TargetLocation;

};

