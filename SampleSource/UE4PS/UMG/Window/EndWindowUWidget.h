// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
// #include "RunTime/UMG/Public/Components/Button.h"

#include "Core/UMG/Window/CoreWindowUWidget.h"
#include "Blueprint/UserWidget.h"
#include "Common/PSDataSchema.h"

#include "EndWindowUWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4PS_API UEndWindowUWidget : public UCoreWindowUWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();
	virtual void ShowWindow(void* arg1 = nullptr, void* arg2 = nullptr);
	virtual void CloseWindow();
	
	void RestartFunc();
	void EndGameFunc();
public :
	
	UTextBlock* m_textTitle;

	UButton* m_BtnReStart;
	UButton* m_BtnEndGame;
	
	
};
