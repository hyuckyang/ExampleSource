// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreWindowUWidget.h"
#include "UE4PSGameModeBase.h"
#include "Common/PSGameInstance.h"
#include "Manager/PSWidgetManager.h"

/*

*/
void UCoreWindowUWidget::NativeConstruct()
{
	GetTopPanel(); GetUE4PSGameMode();
}
/*

*/
void UCoreWindowUWidget::ShowWindow(void* arg1, void* arg2)
{

}

/*

*/
void UCoreWindowUWidget::CloseWindow()
{

}

/*

*/
UPanelWidget* UCoreWindowUWidget::GetTopPanel()
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
AUE4PSGameModeBase* UCoreWindowUWidget::GetUE4PSGameMode()
{
	if (this->m_ue4psGameMode == nullptr)
	{
		this->m_ue4psGameMode = GetWorld()->GetAuthGameMode<AUE4PSGameModeBase>();
	}
	return m_ue4psGameMode;
}

