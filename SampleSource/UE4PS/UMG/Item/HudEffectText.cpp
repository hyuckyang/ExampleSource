// Fill out your copyright notice in the Description page of Project Settings.

#include "HudEffectText.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"

/*
 간단한 내용이라 블루프린트에서 구현하였습니다.
*/
void UHudEffectText::NativeConstruct()
{
	Super::NativeConstruct();

	//m_bSetTargetVector = false;

	m_textBlock = Cast<UTextBlock>(WidgetTree->FindWidget(FName("Text_Num")));

}


void UHudEffectText::NativeTick(const FGeometry& gometry, float deltaTime)
{
	Super::NativeTick(gometry, deltaTime);

	/*if (!m_bSetTargetVector) 
	{
		switch (GetVisibility())
		{
			case ESlateVisibility::Visible:
			case ESlateVisibility::HitTestInvisible:
			case ESlateVisibility::SelfHitTestInvisible:
			{
				SetVisibility(ESlateVisibility::Collapsed);
				return;
			}
		}
	}

	else
	{
		switch (GetVisibility())
		{
			case ESlateVisibility::Hidden:
			case ESlateVisibility::Collapsed:
			{
				SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				return;
			}
		}
	}*/

}


void UHudEffectText::SetTargetPanel(UPanelWidget* panel)
{
	//panel->AddChild(this);

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(panel->AddChild(this));
	slot->SetPosition(slot->GetPosition() + FVector2D(-20.F, 0.F));
}

void UHudEffectText::SetDamegeShow(int32 value)
{
	FString str = FString::Printf(TEXT("%d"), value);
	m_textBlock->SetText(FText::FromString(*str));
}