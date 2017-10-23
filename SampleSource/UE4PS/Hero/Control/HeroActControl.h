// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Camera/CoreCameraControl.h"
#include "HeroActControl.generated.h"

class AHeroActCharacter;
class UFieldWindowUWidget;
/**
 * 
 */
UCLASS()
class UE4PS_API AHeroActControl : public ACoreCameraControl
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// �Է� Action
	void InputMouseWheelUp();
	void InputMouseWheelDown();
	void InputMouseLClickPressed();
	void InputMouseLClickReleased();
	void InputMouseRClickPressed();
	void InputMouseRClickReleased();
	//void InputTapClickPressed() {};
	void InputTapClickReleased();
	void InputSpaceClickReleased();
	// �Է� Axis
	void InputMouseX(float deltaTime);
	void InputMouseY(float deltaTime);
	void InputKeyBoardForward(float deltaTime);
	void InputKeyBoardRight(float deltaTime);

	// ��Ʈ�� Ÿ�� ����
	void SetControlTypeSwap();

	// 
	void SetHeroSelected(AHeroActCharacter* hero);
	//


protected:

	//
	AHeroActCharacter* GetTargetHero();
	//
	UFieldWindowUWidget* m_FieldWindow;
	
};
