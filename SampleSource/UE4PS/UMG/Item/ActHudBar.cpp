// Fill out your copyright notice in the Description page of Project Settings.

#include "ActHudBar.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"

#include "Common/PSDataSchema.h"
#include "Common/PSGameInstance.h"
#include "Core/Act/CoreActCharacter.h"
#include "Hero/Act/HeroActCharacter.h"
#include "PSPlayerController.h"
#include "Manager/PSWidgetManager.h"
#include "UMG/Item/HudEffectText.h"
/*

*/
void UActHudBar::NativeConstruct()
{
	//
	Super::NativeConstruct();
	
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

	//
	// 테스트
	/*bool bVisible = GetWorld()->GetFirstPlayerController()->
		ProjectWorldLocationToScreen(m_ActHudLocate, m_ScreenVec2Pos);*/

	if (m_CanvasSlot == nullptr)return;

	//m_ActHudLocate += FVector(0.f, 60.f, 0.f);

	if (SetPositionFromWorld(m_ActHudLocate, m_CanvasSlot)) 
	{
		m_ActNameTxt->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_ActNameTxt->SetVisibility(ESlateVisibility::Hidden);
	}

	SetVisibility(ESlateVisibility::Visible);

}

/*
 SGUI Plugins 를 참조하였습니다.
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
	UE_LOG(LogClass, Log, TEXT("DAMAEE MINE %s"), *(m_ActNameTxt->Text.ToString()));

	UClass* cls = m_psWidgetManager->GetBlueprintClass(TEXT("/Game/A_Sample/UMG/Item"), TEXT("BP_DamageText"));
	if (cls == nullptr) return;

	UUserWidget* widget = CreateWidget<UUserWidget>(m_psGameInstance->GetWorld(), cls);
	if (widget == nullptr) return;

	UHudEffectText* effecttext = CreateWidget<UHudEffectText>(m_psGameInstance->GetWorld(), cls);

	
	UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(m_ParentPanel->AddChild(effecttext));
	//UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(m_ParentPanel->AddChild(effecttext));

	FVector2D vec2d = m_CanvasSlot->GetPosition() + FVector2D(-20.f, 0.f);
	canvasSlot->SetPosition(vec2d);
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

