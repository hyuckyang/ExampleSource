// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/WidgetSwitcher.h"
#include "ActHudBar.generated.h"

class APSPlayerController;
class ACoreActCharacter;
/**
 * 
 */
UCLASS()
class UE4PS_API UActHudBar : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& gometry, float deltaTime);
	
	/*void SetPSGameInstance(UPSGameInstance* instance) { this->m_psGameInstance = instance; }
	void SetPSWidgetManager(UPSWidgetManager* wdmanager) { this->m_psWidgetManager = wdmanager; }*/
	
	void AddToCharacterInfo(ACoreActCharacter* character);
	void AddToParentPanel(UPanelWidget* panel);

	// SGUI Plugins ÂüÁ¶
	bool SetPositionFromWorld(FVector vec3, UCanvasPanelSlot* slot = nullptr, FVector2D pivot = FVector2D::ZeroVector);

	void ToDamageShow(int32 damageValue);

	void SelectToItem(bool bSelect);
protected:
	
	class UPSGameInstance*	m_psGameInstance		= nullptr;
	class UPSWidgetManager*	m_psWidgetManager		= nullptr;

	UPanelWidget*			m_ParentPanel;
	UCanvasPanelSlot*		m_CanvasSlot;
	
	UWidgetSwitcher*		m_SelectSwitcher;
	UTextBlock*				m_ActNameTxt;
	UTextBlock*				m_ActRNameTxt;

	UProgressBar*			m_ProgressHP;


	UPanelWidget*			m_PanelWidget;

	//
	APSPlayerController*	m_psPlayerController	= nullptr;
	ACoreActCharacter*		m_ActCharacter			= nullptr;;
	
	FVector					m_ActHudLocate;
	FVector2D				m_ScreenVec2Pos;
	
};
