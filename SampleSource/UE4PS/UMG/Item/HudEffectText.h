// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
};
