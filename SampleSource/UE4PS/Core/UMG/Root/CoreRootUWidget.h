// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
//#include "Blueprint/UserWidget.h"
#include "CoreRootUWidget.generated.h"


class AUE4PSGameModeBase;
class UPSGameInstance;
class UPSWidgetManager;
/**
 * 
 */
UCLASS()
class UE4PS_API UCoreRootUWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct();

	/*
	Get Func..
	*/
	UPanelWidget*		GetTopPanel();
	AUE4PSGameModeBase* GetUE4PSGameMode();
	UPSGameInstance*	GetPSGameInstance();
	UPSWidgetManager*	GetWidgetManager();

	/*
	*/
	/*UWidget* FindWidget(const FName _name);*/

protected:

	UPanelWidget*		m_topPanel			= nullptr;
	AUE4PSGameModeBase* m_ue4psGameMode		= nullptr;
	UPSGameInstance*	m_psGameInstance	= nullptr;
	UPSWidgetManager*	m_psWidgetManager	= nullptr;
};



