// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
// #include "Blueprint/UserWidget.h"
#include "CoreWindowUWidget.generated.h"

class AUE4PSGameModeBase;
class UPSGameInstance;
class UPSWidgetManager;
/**
 * 
 */
UCLASS()
class UE4PS_API UCoreWindowUWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	
	virtual void NativeConstruct();

	virtual void ShowWindow(void* arg1 = nullptr, void* arg2 = nullptr);
	virtual void CloseWindow();

	void SetPSGameInstance(UPSGameInstance* instance)		{ this->m_psGameInstance = instance; }
	void SetPSWidgetManager(UPSWidgetManager* wdmanager)	{ this->m_psWidgetManager = wdmanager; }
protected :

	/*
	Get Func..
	*/
	UPanelWidget*		GetTopPanel();
	AUE4PSGameModeBase* GetUE4PSGameMode();
	
	template<typename T>
	T* FindWidget(const FName _name) { return Cast<T>(WidgetTree->FindWidget(_name)); }
protected:

	UPanelWidget*		m_topPanel			= nullptr;
	AUE4PSGameModeBase* m_ue4psGameMode		= nullptr;
	UPSGameInstance*	m_psGameInstance	= nullptr;
	UPSWidgetManager*	m_psWidgetManager	= nullptr;

	bool m_bRootUI = false;
	bool m_bFullWindow = false;

};
