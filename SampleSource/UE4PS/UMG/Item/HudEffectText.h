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
#include "HudEffectText.generated.h"


/**
 * 
 */
UCLASS()
class UE4PS_API UHudEffectText : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EffectAnimation")
	class UWidgetAnimation* m_effctAnim;
	
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& gometry, float deltaTime);

	void SetTargetPanel(UPanelWidget* panel);
	void SetDamegeShow(int32 value);

protected:
	//bool	m_bSetTargetVector	= false;
	//FVector m_targetVector		= FVector::ZeroVector;;
	UTextBlock* m_textBlock;
	
};
