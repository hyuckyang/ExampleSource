// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Camera/CoreCameraControl.h"
#include "Materials/Material.h"
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
	
	AHeroActControl();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// 입력 Action
	void InputMouseWheelUp();
	void InputMouseWheelDown();
	void InputMouseLClickPressed();
	void InputMouseLClickReleased();
	void InputMouseRClickPressed();
	void InputMouseRClickReleased();
	//void InputTapClickPressed() {};
	void InputTapClickReleased();
	void InputSpaceClickReleased();
	void InputBWeaponSwitcherReleased();
	// 입력 Axis
	void InputMouseX(float deltaTime);
	void InputMouseY(float deltaTime);
	void InputKeyBoardForward(float deltaTime);
	void InputKeyBoardRight(float deltaTime);

	// 컨트롤 타입 변경
	void SetControlTypeSwap();
	//
	void SetHeroSelected(AHeroActCharacter* hero);
	

protected :
	
	AHeroActCharacter*	 GetTargetHero();
	
protected:

	UFieldWindowUWidget* m_FieldWindow;
	UDecalComponent*	 m_DecalToCursur;

	//bool				 m_bMoveKeyHasPressed = false;
};
