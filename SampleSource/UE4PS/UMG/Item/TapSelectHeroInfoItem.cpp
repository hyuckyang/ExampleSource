// Fill out your copyright notice in the Description page of Project Settings.

#include "TapSelectHeroInfoItem.h"
#include "Hero/Act/HeroActCharacter.h"

void UTapSelectHeroInfoItem::NativeConstruct()
{
	/*m_SelectSwitcher = Cast<UWidgetSwitcher>(WidgetTree->FindWidget(TEXT("Bg_ChoiceSwitcher")));
	m_SelectNameTxt = Cast<UTextBlock>(WidgetTree->FindWidget(TEXT("Text_Name")));*/
	//if (m_SelectNameTxt != nullptr) m_SelectNameTxt->SetText(FText::FromString("TEXT OK"));
}

void UTapSelectHeroInfoItem::AddToHeroInfo(AHeroActCharacter* hero)
{
	if (hero == nullptr) return;

	// NativeConstruct 보다 먼저 실행되는 경우가 있음. 위젯 생성후 다음 프레임이 아닌 바로 그 프레임에 이 함수로 넘어올 경우..
	if (m_SelectNameTxt == nullptr)	
		m_SelectNameTxt = Cast<UTextBlock>(WidgetTree->FindWidget(TEXT("Text_Name")));

	m_SelectNameTxt->SetText(FText::FromString(hero->GetName()));

	m_HeroUniqueID = hero->GetUniqueID();
}

void UTapSelectHeroInfoItem::SelectToItem(bool bSelect)
{
	if (m_SelectSwitcher == nullptr)
		m_SelectSwitcher = Cast<UWidgetSwitcher>(WidgetTree->FindWidget(TEXT("Bg_ChoiceSwitcher")));

	m_SelectSwitcher->SetActiveWidgetIndex(bSelect == true ? 1 : 0);
}