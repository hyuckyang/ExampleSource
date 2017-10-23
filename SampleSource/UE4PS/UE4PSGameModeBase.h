// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE4PSGameModeBase.generated.h"

class UPSGameInstance;
class UPSActorManager;
class UPSWidgetManager;
class APSPlayerController;

/**
 * 
 */
UCLASS()
class UE4PS_API AUE4PSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	//
	void SetViewFadeOut(float time);
	
protected:
	UPSGameInstance*		m_psGameInstance;
	UPSActorManager*		m_psActorManager;
	UPSWidgetManager*		m_psWidgetManager;

	APSPlayerController*	m_psController;;

	
	
};
