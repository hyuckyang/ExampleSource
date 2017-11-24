// Fill out your copyright notice in the Description page of Project Settings.

#include "PSWidgetManager.h"
//#include "Core/UMG/Root/CoreRootUWidget.h"
#include "Core/UMG/Window/CoreWindowUWidget.h"

UClass* UPSWidgetManager::GetBlueprintClass(const FString& path, const FString& name) 
{
	FString toPath = FString::Printf(TEXT("WidgetBlueprint'%s/%s.%s_C'"), *path, *name, *name);

	UClass* bpGC = LoadObject<UBlueprintGeneratedClass>(m_psGameInstance->GetOuter(), *toPath);

	return bpGC != nullptr ? bpGC : nullptr;

	/*if (!m_BPWidgetClsList.Contains(*toPath))
	{
		UClass* bpGC = LoadObject<UBlueprintGeneratedClass>(m_psGameInstance->GetOuter(), *toPath);
		if (bpGC == nullptr)
			return nullptr;
			m_BPWidgetClsList.Emplace(toPath, bpGC);
	}
	return m_BPWidgetClsList[*toPath];*/
}

UClass* UPSWidgetManager::GetWindowClass(eWindowID windowID)
{
	FString enumStr = UPSDataSchema::GetEnumString<eWindowID>("eWindowID", windowID);
	FString bpStr = FString::Printf(TEXT("BP_%s"), *enumStr);
	UClass* cls = GetBlueprintClass("/Game/A_Sample/UMG/Window", *bpStr);

	return cls != nullptr ? cls : nullptr;
}

bool UPSWidgetManager::AddToWindowWidget(eWindowID windowID)
{
	if (m_windowWidgets.Contains(windowID)) return true;

	UClass* cls = GetWindowClass(windowID);
	if (cls == nullptr) return false;

	UCoreWindowUWidget* window = CreateWidget<UCoreWindowUWidget>(m_psGameInstance->GetWorld(), cls);
	if (window == nullptr) return false;

	window->SetPSGameInstance(this->m_psGameInstance);
	window->SetPSWidgetManager(this);
	window->SetVisibility(ESlateVisibility::Collapsed);

	m_windowWidgets.Emplace(windowID, window);
	return true;
}

void UPSWidgetManager::PushToWindow(eWindowID windowID, void* arg1, void* arg2)
{
	if (!m_windowWidgets.Contains(windowID))
	{
		bool bAdd = AddToWindowWidget(windowID);
		if (!bAdd) return;
	}

	UCoreWindowUWidget* coreWidget = m_windowWidgets[windowID];
	
	coreWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	coreWidget->AddToViewport(m_windowStack.Num() + 1);
	coreWidget->ShowWindow(arg1, arg2);

	
	m_windowStack.Push(coreWidget);
}


void UPSWidgetManager::PopToWindow()
{
	UCoreWindowUWidget* coreWidget = m_windowStack.Pop();

	coreWidget->SetVisibility(ESlateVisibility::Collapsed);
	coreWidget->RemoveFromViewport();
}

UCoreWindowUWidget* UPSWidgetManager::GetTopWindow()
{
	int lastIdx = m_windowStack.Num() - 1;
	if (!m_windowStack.IsValidIndex(lastIdx))
	{
		return nullptr;
	}

	return m_windowStack[lastIdx];
}


