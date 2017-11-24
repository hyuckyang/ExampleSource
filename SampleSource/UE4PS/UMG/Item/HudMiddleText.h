// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
//#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "HudMiddleText.generated.h"

/**
 * 
 */
UCLASS()
class UE4PS_API UHudMiddleText : public UUserWidget
{
	GENERATED_BODY()
	
public :
	virtual void NativeConstruct();
	void EffectHudText(FString str);
	

	
	// Test Сп
	UFUNCTION(BlueprintImplementableEvent)
	void SetEffectWidgetAnim(class UWidgetAnimation* inAnim, class UWidgetAnimation* outAnim);
	void SetEffectWidgetAnim_Implementation(class UWidgetAnimation* inAnim, class UWidgetAnimation* outAnim);


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EffectAnimation")
	class UWidgetAnimation* m_inEffectAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EffectAnimation")
	class UWidgetAnimation* m_outEffectAnim;

	UTextBlock* m_textBlock;
};
