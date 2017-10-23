// Fill out your copyright notice in the Description page of Project Settings.

#include "ActHudBar.h"
#include "Common/PSDataSchema.h"
#include "Core/Act/CoreActCharacter.h"
#include "PSPlayerController.h"

/*

*/
void UActHudBar::NativeConstruct()
{
	//
	//m_psPlayerController = getfirst

	UE_LOG(LogClass, Log, TEXT("NativeConstruct"));
}

/*

*/
void UActHudBar::NativeTick(const FGeometry& gometry, float deltaTime)
{
	
	if (m_ActCharacter == nullptr) return;
	if (m_ActCharacter->GetCurrentStateID() == eStateID::DEAD) 
	{
		// 캐릭터가 죽었을 때. 객체 삭제 혹은 Disable
		return;
	}

	if (!m_ActCharacter->GetHudSocketLoaction(m_ActHudLocate)) return;

	//
	// 테스트
	bool bVisible = GetWorld()->GetFirstPlayerController()->
		ProjectWorldLocationToScreen(m_ActHudLocate, m_ScreenVec2Pos);

	if (m_CanvasSlot == nullptr)return;

	m_CanvasSlot->SetPosition(m_ScreenVec2Pos);

	m_ActNameTxt->SetVisibility(ESlateVisibility::Visible);

	//if (m_PanelSlot == nullptr)return;

	
	/*m_PanelSlot->Parent->setposition*/
	//SetPosition
	//postion
	//SetPositionInViewport(m_ScreenVec2Pos);
	/*SetVisibility(ESlateVisibility::Visible);

	switch (GetVisibility())
	{
	case ESlateVisibility::Collapsed:
	case ESlateVisibility::Hidden:
		UE_LOG(LogClass, Log, TEXT("HUD BAR DISABLE"));
		break;
	default:
		UE_LOG(LogClass, Log, TEXT("HUD BAR VISIBLE"));
		break;
	}
	UE_LOG(LogClass, Log, TEXT("NativeTick"));*/
	//SetVisibility(bVisible == true ? ESlateVisibility::Hidden : ESlateVisibility::Visible);

}

/*

*/
//void UActHudBar::SetPSGameInstance(UPSGameInstance* instance)
//{
//	m_psGameInstance = instance; 
//	m_psGameInstance->Getwo
//}

/*

*/
void UActHudBar::AddToCharacterInfo(ACoreActCharacter* character)
{
	if (m_ActNameTxt == nullptr)
		m_ActNameTxt = Cast<UTextBlock>(WidgetTree->FindWidget(TEXT("Name_TBlock")));

	//m_ActNameTxt->SetText(FText::FromString())
	m_ActCharacter = character;
}

void UActHudBar::AddToParentPanel(UPanelWidget* panel)
{
	m_CanvasSlot = Cast<UCanvasPanelSlot>(panel->AddChild(this));
}

