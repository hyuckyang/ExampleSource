// Fill out your copyright notice in the Description page of Project Settings.

#include "ActHudBar.h"

#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Components/WidgetComponent.h"
#include "PSPlayerController.h"

#include "Common/PSDataSchema.h"
#include "Common/PSGameInstance.h"
#include "UMG/Item/HudEffectText.h"
#include "Manager/PSWidgetManager.h"
#include "Core/Act/CoreActCharacter.h"
#include "Hero/Act/HeroActCharacter.h"



/*

*/
void UActHudBar::NativeConstruct()
{
	//
	Super::NativeConstruct();

	m_PanelWidget = Cast<UPanelWidget>(WidgetTree->FindWidget(FName("CanvasPanel_0")));
	m_ProgressHP = Cast<UProgressBar>(WidgetTree->FindWidget(FName("HP_PBar")));
	m_ProgressHP->SetPercent(1.f);
	
}

/*

*/
void UActHudBar::NativeTick(const FGeometry& gometry, float deltaTime)
{
	Super::NativeTick(gometry, deltaTime);

	if (m_ActCharacter == nullptr) return;
	if (m_ActCharacter->GetCurrentStateID() == eStateID::DEATH)
	{
		// 캐릭터가 죽었을 때. 객체 삭제 혹은 Disable
		return;
	}

	if (!m_ActCharacter->GetHudSocketLoaction(m_ActHudLocate)) return;
}

/*
 SGUI Plugins 를 참조하였습니다. WidgetComponent 사용해서 아래 함수 사용.. 안합니다.
*/
bool UActHudBar::SetPositionFromWorld(FVector vec3, UCanvasPanelSlot* slot, FVector2D pivot)
{
	if (m_ActCharacter == nullptr) return false;
	if (slot == nullptr) return false;

	FVector2D screenPos;

	bool isInVPort = GetWorld()->GetFirstPlayerController()->
		ProjectWorldLocationToScreen(vec3, screenPos);

	screenPos += FVector2D(-60.f, 0.f);

	FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	if (slot)
	{
		float vpScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(viewportSize.X, viewportSize.Y));
		slot->SetPosition(screenPos / vpScale);

	}
	/*else
	{
		
	}*/

	return isInVPort;
}

/*

*/
void UActHudBar::ToDamageShow(int32 damageValue) 
{
	// UE_LOG(LogClass, Log, TEXT("DAMAEE MINE %s"), *(m_ActNameTxt->Text.ToString()));

	UClass* cls = m_psWidgetManager->GetBlueprintClass(TEXT("/Game/A_Sample/UMG/Item"), TEXT("BP_DamageText"));
	if (cls == nullptr) return;

	UUserWidget* widget = CreateWidget<UUserWidget>(m_psGameInstance->GetWorld(), cls);
	if (widget == nullptr) return;

	UHudEffectText* effecttext = CreateWidget<UHudEffectText>(m_psGameInstance->GetWorld(), cls);

	effecttext->SetTargetPanel(m_PanelWidget);
	effecttext->SetDamegeShow(damageValue);

	float persent = (float)m_ActCharacter->m_CurrentHP / (float)m_ActCharacter->m_PointHealth;
	m_ProgressHP->SetPercent(persent);
}

/*

*/
void UActHudBar::AddToCharacterInfo(ACoreActCharacter* character)
{
	if (m_ActNameTxt == nullptr)
		m_ActNameTxt = Cast<UTextBlock>(WidgetTree->FindWidget(TEXT("Name_TBlock")));

	if (character->GetCurrentActorTypeID() == eActorTypeID::HERO) 
	{
		AHeroActCharacter* hero = Cast<AHeroActCharacter>(character);
		if (hero != nullptr) 
		{
			m_ActNameTxt->SetText(FText::FromString(hero->GetName()));
		}
	}
	else
	{
		m_ActNameTxt->SetText(FText::GetEmpty());
	}

	//
	character->ReceiveDamageFuncBind(this, &UActHudBar::ToDamageShow);
	//

	m_psGameInstance = Cast<UPSGameInstance>(character->GetGameInstance());
	m_psWidgetManager = m_psGameInstance->GetWidgetManager();

	m_ActCharacter = character;
}

void UActHudBar::AddToParentPanel(UPanelWidget* panel)
{
	m_ParentPanel = panel;
	m_CanvasSlot = Cast<UCanvasPanelSlot>(panel->AddChild(this));
}

