// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Common/PSGameInstance.h"
#include "PSBaseManager.generated.h"

/**
 * 
 */
UCLASS()
class UE4PS_API UPSBaseManager : public UObject
{
	GENERATED_BODY()
	

public:
	
	UPSBaseManager();

	virtual void SetPSGameInstance(UPSGameInstance* instance) { this->m_psGameInstance = instance; }
	virtual class UWorld* GetWorld() const;

protected:

	UPSGameInstance* m_psGameInstance;
};
