// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
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
	
	void AddToCharacterInfo(ACoreActCharacter* character);
	void AddToParentPanel(UPanelWidget* panel);
protected:
	
	//UPanelWidget*			m_ParentPanel;
	UCanvasPanelSlot*		m_CanvasSlot;
	/*UPanelSlot*				m_PanelSlot;*/
	UTextBlock*				m_ActNameTxt;

	//
	APSPlayerController*	m_psPlayerController	= nullptr;
	ACoreActCharacter*		m_ActCharacter			= nullptr;;
	
	FVector					m_ActHudLocate;
	FVector2D				m_ScreenVec2Pos;



	
};
