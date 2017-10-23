// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/WidgetSwitcher.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "TapSelectHeroInfoItem.generated.h"

class AHeroActCharacter;
/**
 * 
 */
UCLASS()
class UE4PS_API UTapSelectHeroInfoItem : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct();
	void AddToHeroInfo(AHeroActCharacter* hero);
	void SelectToItem(bool bSelect);
	int32 GetHeroUniqueID() { return m_HeroUniqueID; }

public:
	
	UPROPERTY()
	UWidgetSwitcher* m_SelectSwitcher;
	
	UPROPERTY()
	UTextBlock* m_SelectNameTxt;	

	int32 m_HeroUniqueID = 0;
};
