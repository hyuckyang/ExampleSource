// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreRootUWidget.h"
#include "UE4PSGameModeBase.h"
#include "Common/PSGameInstance.h"
#include "Manager/PSWidgetManager.h"

/*

*/
void UCoreRootUWidget::NativeConstruct()
{
	GetTopPanel(); GetUE4PSGameMode(); GetPSGameInstance(); GetWidgetManager();
}

/*

*/
UPanelWidget* UCoreRootUWidget::GetTopPanel()
{
	if (this->m_topPanel == nullptr)
	{
		UWidget* findWidget = WidgetTree->FindWidget(TEXT("TopPaenl"));
		if (findWidget == nullptr)return nullptr;

		this->m_topPanel = Cast<UPanelWidget>(findWidget);
	}
	return nullptr;
}

/*

*/
AUE4PSGameModeBase* UCoreRootUWidget::GetUE4PSGameMode()
{
	if (this->m_ue4psGameMode == nullptr)
	{
		this->m_ue4psGameMode = GetWorld()->GetAuthGameMode<AUE4PSGameModeBase>();
	}
	return m_ue4psGameMode;
}

/*

*/
UPSGameInstance* UCoreRootUWidget::GetPSGameInstance()
{
	if (this->m_psGameInstance == nullptr)
	{
		this->m_psGameInstance = Cast<UPSGameInstance>(this->GetPSGameInstance());
	}
	return this->m_psGameInstance;
}

/*

*/
UPSWidgetManager* UCoreRootUWidget::GetWidgetManager()
{
	if (this->m_psWidgetManager == nullptr)
	{
		this->m_psWidgetManager = GetPSGameInstance()->GetWidgetManager();
	}
	return this->m_psWidgetManager;
}

/*

*/



