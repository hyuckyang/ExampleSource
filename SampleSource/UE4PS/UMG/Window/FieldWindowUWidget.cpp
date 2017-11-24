// Fill out your copyright notice in the Description page of Project Settings.

#include "FieldWindowUWidget.h"

#include "UMG/Item/ActHudBar.h"
#include "UMG/Item/HudMiddleText.h"
#include "Manager/PSWidgetManager.h"
#include "Core/Act/CoreActCharacter.h"
#include "Hero/Act/HeroActCharacter.h"
#include "UMG/Item/TapSelectHeroInfoItem.h"


void UFieldWindowUWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//
	m_hudPanel			= FindWidget<UPanelWidget>(TEXT("HudPanel"));
	m_keyModePanel		= FindWidget<UPanelWidget>(TEXT("InputMode_Keymode"));
	m_rtsModePanel		= FindWidget<UPanelWidget>(TEXT("InputMode_MouseMode"));
	m_heroListScrollBox = FindWidget<UScrollBox>(TEXT("ScrollBox_0"));
	m_heroListWrapBox	= FindWidget<UWrapBox>(TEXT("WrapBox_1"));	

	m_GoalValueBar		= Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("GoalHPBar")));
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

/*

*/
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
}

/*

*/
void UFieldWindowUWidget::SelectToHeroInfo(int32 uniqueID)
{
	for (int loop = 0, max = m_TapHeroItems.Num(); loop < max; ++loop)
	{
		UTapSelectHeroInfoItem* current = m_TapHeroItems[loop];
		current->SelectToItem(current->GetHeroUniqueID() == uniqueID ? true : false);
	}
}

/*

*/
void UFieldWindowUWidget::SetGoalUpdateValue(int32 value, int32 total)
{
	// UE_LOG(LogClass, Log, TEXT("UFieldWindowUWidget::SetGoalUpdateValue"));

	if (m_GoalValueBar == nullptr) return;

	float persent = (float)value / (float)total;
	

	m_GoalValueBar->SetPercent(persent);
}

/*

*/
UHudMiddleText* UFieldWindowUWidget::SetWaveInfoTextPrint(FString str)
{
	UClass* cls = m_psWidgetManager->GetBlueprintClass(TEXT("/Game/A_Sample/UMG/Item"), TEXT("BP_MiddleText"));
	if (cls == nullptr) return nullptr;

	UHudMiddleText* item = CreateWidget<UHudMiddleText>(m_psGameInstance->GetWorld(), cls);
	if (item == nullptr) return nullptr;

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(GetTopPanel()->AddChild(item));
	FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	// 이렇게  오프셋을 설정하면 안되...
	slot->SetPosition(FVector2D(460.f, 450.f));
	item->EffectHudText(str);

	return item;
}

/*
 사실상 사용하지 않음.
 */
void UFieldWindowUWidget::GiveToHeadBar(ACoreActCharacter* core)
{
	UClass* cls = m_psWidgetManager->GetBlueprintClass(TEXT("/Game/A_Sample/UMG/Item"), TEXT("BP_ActHudBar"));
	if (cls == nullptr)return;

	UActHudBar* hudBar = CreateWidget<UActHudBar>(m_psGameInstance->GetWorld(), cls);
	if (hudBar == nullptr) return;

	hudBar->AddToCharacterInfo(core);
	hudBar->AddToParentPanel(m_hudPanel);
}