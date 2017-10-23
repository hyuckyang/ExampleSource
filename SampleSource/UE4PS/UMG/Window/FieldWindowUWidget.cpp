// Fill out your copyright notice in the Description page of Project Settings.

#include "FieldWindowUWidget.h"
#include "Manager/PSWidgetManager.h"
#include "UMG/Item/ActHudBar.h"
#include "UMG/Item/TapSelectHeroInfoItem.h"
#include "Hero/Act/HeroActCharacter.h"

void UFieldWindowUWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//
	m_hudPanel			= FindWidget<UPanelWidget>(TEXT("HudPanel"));
	m_keyModePanel		= FindWidget<UPanelWidget>(TEXT("InputMode_Keymode"));
	m_rtsModePanel		= FindWidget<UPanelWidget>(TEXT("InputMode_MouseMode"));
	m_heroListScrollBox = FindWidget<UScrollBox>(TEXT("ScrollBox_0"));
	m_heroListWrapBox	= FindWidget<UWrapBox>(TEXT("WrapBox_1"));

	
}

/*

*/
void UFieldWindowUWidget::ShowWindow(void* arg1, void* arg2)
{
	Super::ShowWindow(arg1, arg2);
	m_keyModePanel->SetVisibility(ESlateVisibility::Collapsed);
	m_rtsModePanel->SetVisibility(ESlateVisibility::Collapsed);
}

/*

*/
void UFieldWindowUWidget::CloseWindow()
{
	Super::CloseWindow();
}

/*

*/
void UFieldWindowUWidget::SetToControlMode(eCameraControlID controlID)
{
	m_keyModePanel->SetVisibility(ESlateVisibility::Collapsed);
	m_rtsModePanel->SetVisibility(ESlateVisibility::Collapsed);

	switch (controlID)
	{
	case eCameraControlID::TARGET:
		m_keyModePanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case eCameraControlID::FREE:
		m_rtsModePanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	default:
		break;
	}
}

void UFieldWindowUWidget::AddToHeroInfo(AHeroActCharacter* hero)
{
	/*
	*/
	UClass* cls = m_psWidgetManager->GetBlueprintClass(TEXT("/Game/A_Sample/UMG/Item"), TEXT("BP_TapSelectHeroInfoItem"));
	if (cls == nullptr) return;
	
	UTapSelectHeroInfoItem* heroItem = CreateWidget<UTapSelectHeroInfoItem>(m_psGameInstance->GetWorld(), cls);
	if (heroItem == nullptr)return;

	heroItem->AddToHeroInfo(hero);
	
	if (m_heroListWrapBox == nullptr) { UE_LOG(LogClass, Log, TEXT("m_heroListWrapBox == nullptr")); return; }

	m_TapHeroItems.Emplace(heroItem);
	m_heroListWrapBox->AddChild(heroItem);

	/*
	±¸Çö Áß
	*/
	return;
	cls = nullptr;
	cls = m_psWidgetManager->GetBlueprintClass(TEXT("/Game/A_Sample/UMG/Item"), TEXT("BP_ActHudBar"));
	if (cls == nullptr)return;

	UActHudBar* hudBar = CreateWidget<UActHudBar>(m_psGameInstance->GetWorld(), cls);
	if (hudBar == nullptr) return;

	hudBar->AddToCharacterInfo(hero);
	hudBar->AddToParentPanel(m_hudPanel);
	
	//hudBar->AddToViewport(0);
	//m_hudPanel->AddChild(hudBar);
}

void UFieldWindowUWidget::SelectToHeroInfo(int32 uniqueID)
{

	for (int loop = 0, max = m_TapHeroItems.Num(); loop < max; ++loop)
	{
		UTapSelectHeroInfoItem* current = m_TapHeroItems[loop];
		current->SelectToItem(current->GetHeroUniqueID() == uniqueID ? true : false);

		//UE_LOG(LogClass, Log, TEXT("GetHeroUniqueID : %d, uniqueID : %d"), current->GetHeroUniqueID(), uniqueID);
	}

}