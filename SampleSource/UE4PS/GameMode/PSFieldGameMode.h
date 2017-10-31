// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE4PSGameModeBase.h"
#include "PSFieldGameMode.generated.h"

class AHeroActControl;
class UFieldWindowUWidget;
/**
 * 
 */
UCLASS()
class UE4PS_API APSFieldGameMode : public AUE4PSGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// 필드 유아이를 셋팅한다.
	void SetFieldWindow();

protected:
	 
	AHeroActControl*	 m_HeroControl;
	UFieldWindowUWidget* m_FieldWindow;

	int ticks = 0;
};
