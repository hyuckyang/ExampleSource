// Fill out your copyright notice in the Description page of Project Settings.

#include "HudMiddleText.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"

void UHudMiddleText::NativeConstruct()
{
	Super::NativeConstruct();

	//UE_LOG(LogClass, Log, TEXT("ue4 nativeContruct"));

	m_textBlock = Cast<UTextBlock>(WidgetTree->FindWidget(FName("Text_Event")));
}

void UHudMiddleText::EffectHudText(FString str)
{
	/*if (m_inEffectAnim == nullptr) 
	{
		UE_LOG(LogClass, Log, TEXT("m_inEffectAnim == nullptr"));
	}

	if (m_outEffectAnim == nullptr) 
	{
		UE_LOG(LogClass, Log, TEXT("m_outEffectAnim == nullptr"));
	}*/

	m_textBlock->SetText(FText::FromString(*str));

	//PlayAnimation(m_inEffectAnim);
	//m_inEffectAnim->
	
}

//void UHudMiddleText::SetEffectWidgetAnim(UWidgetAnimation* inAnim, UWidgetAnimation* outAnim)
//{
//}
void UHudMiddleText::SetEffectWidgetAnim_Implementation(UWidgetAnimation* inAnim, UWidgetAnimation* outAnim)
{

}
