// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/PSBaseManager.h"
#include "Common/PSDataSchema.h"
#include "PSDataManager.generated.h"

/**
 * 
 */
UCLASS()
class UE4PS_API UPSDataManager : public UPSBaseManager
{
	GENERATED_BODY()


	//UDataTable* m_CharacterInfoData;
	TArray<FCharacterData> m_CharacterData;

public:
	
	UPSDataManager();

	/*

	*/
	TArray<FCharacterData> GetCharacterData() { return m_CharacterData; }

	template<typename T>
	bool SetDataTableTArray(TArray<T>& arr, FString DocumentName);

	UDataTable* GetDataTable(const FString& DocumentName);
	

};