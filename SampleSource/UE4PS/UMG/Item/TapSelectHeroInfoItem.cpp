// Fill out your copyright notice in the Description page of Project Settings.

#include "TapSelectHeroInfoItem.h"
#include "Hero/Act/HeroActCharacter.h"

void UTapSelectHeroInfoItem::NativeConstruct()
{
}

void UTapSelectHeroInfoItem::AddToHeroInfo(AHeroActCharacter* hero)
{
	if (hero == nullptr) return;

	// NativeConstruct ���� ���� ����Ǵ� ��찡 ����. ���� ������ ���� �������� �ƴ� �ٷ� �� �����ӿ� �� �Լ��� �Ѿ�� ���..
	if (m_NameText == nullptr)		m_NameText		= Cast<UTextBlock>(WidgetTree->FindWidget(TEXT("Text_Name")));
	if (m_WeaponText == nullptr)	m_WeaponText	= Cast<UTextBlock>(WidgetTree->FindWidget(TEXT("Text_Weapon")));
	if (m_HpBar == nullptr)			m_HpBar			= Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("ProgressBar_HP")));

	//
	m_NameText->SetText(FText::FromString(hero->GetName()));
	//
	hero->ReceiveDamageFuncBind(this, &UTapSelectHeroInfoItem::ToDamageShow);
	hero->SwitcherWTriggerFuncBind(this, &UTapSelectHeroInfoItem::SetWeaponTriggerID);

	SetWeaponTriggerID(hero->GetWeaponTriggerID());
	//
	m_HeroUniqueID = hero->GetUniqueID();
}

void UTapSelectHeroInfoItem::SelectToItem(bool bSelect)
{
	if (m_SelectSwitcher == nullptr)
		m_SelectSwitcher = Cast<UWidgetSwitcher>(WidgetTree->FindWidget(TEXT("Bg_ChoiceSwitcher")));

	m_SelectSwitcher->SetActiveWidgetIndex(bSelect == true ? 1 : 0);
}

void UTapSelectHeroInfoItem::SetWeaponTriggerID(eWeaponTriggerID triggerID)
{
	switch (triggerID)
	{
		case eWeaponTriggerID::SEMIAUTO:
		{
			m_WeaponText->SetText(FText::FromString(TEXT("Semi-Auto")));
			break;
		}
		case eWeaponTriggerID::BURST:
		{
			m_WeaponText->SetText(FText::FromString(TEXT("Burst")));
			break;
		}
		case eWeaponTriggerID::FULLAUTO:
		{
			m_WeaponText->SetText(FText::FromString(TEXT("Full-Auto")));
			break;
		}
		default:
		{
			break;
		}
	}
}