// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/PSDataSchema.h"
#include "RunTime/UMG/Public/Components/ScrollBox.h"
#include "RunTime/UMG/Public/Components/WrapBox.h"
#include "Core/UMG/Window/CoreWindowUWidget.h"
#include "FieldWindowUWidget.generated.h"

class UActHudBar;
class UTapSelectHeroInfoItem;
class ACoreActCharacter;
class AHeroActCharacter;
/**
 * 
 */
UCLASS()
class UE4PS_API UFieldWindowUWidget : public UCoreWindowUWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct();
	virtual void ShowWindow(void* arg1 = nullptr, void* arg2 = nullptr);
	virtual void CloseWindow();

	void SetToControlMode(eCameraControlID controlID);
	void AddToHeroInfo(AHeroActCharacter* hero);

	void SelectToHeroInfo(int32 uniqueID);
	
	// �Ӹ� ���� HudBar �ο�
	void GiveToHeadBar(ACoreActCharacter* core);
	
public :
	
	UPanelWidget*	m_hudPanel;
	UPanelWidget*	m_keyModePanel;
	UPanelWidget*	m_rtsModePanel;

	UScrollBox*		m_heroListScrollBox;
	UWrapBox*		m_heroListWrapBox;

protected:

	TArray<UTapSelectHeroInfoItem*> m_TapHeroItems;


};
