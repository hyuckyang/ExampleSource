// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/PSDataSchema.h"
#include "Manager/PSBaseManager.h"
#include "UObject/NoExportTypes.h"
#include "PSWidgetManager.generated.h"

//class UCoreRootUWidget;
class UCoreWindowUWidget;
/**
 * 
 */
UCLASS()
class UE4PS_API UPSWidgetManager : public UPSBaseManager
{
	
	GENERATED_BODY()
	
public:

	//UClass* GetRootClass(eRootUIID rootUI);
	UClass* GetWindowClass(eWindowID windowID);
	UClass* GetBlueprintClass(const FString& path, const FString& name);
	

	//
	bool AddToWindowWidget(eWindowID windowID);
	void PushToWindow(eWindowID windowID, void* arg1 = nullptr, void* arg2 = nullptr);
	void PopToWindow();

	UCoreWindowUWidget* GetTopWindow();
protected:

	// TMap<FString, UClass*>					m_bpWidgetClsList;
	TMap<eWindowID, UCoreWindowUWidget*>	m_windowWidgets;
	TArray<UCoreWindowUWidget*>				m_windowStack;



};
