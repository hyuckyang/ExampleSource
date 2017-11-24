// Fill out your copyright notice in the Description page of Project Settings.

#include "PSDataManager.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

UPSDataManager::UPSDataManager() :Super()
{
	// 
	SetDataTableTArray(m_CharacterData, FString("FCharacterData"));
}

//void UPSDataManager::OnLoadTableData()
//{
//	
//}

template<typename T>
bool UPSDataManager::SetDataTableTArray(TArray<T>& arr, FString DocumentName)
{
	UDataTable*  data = GetDataTable(DocumentName);
	if (data == nullptr) return false;

	for (int loop = 0, max = data->RowMap.Num(); loop < max; loop++)
	{
		FString str = FString::Printf(TEXT("%d"), loop + 1);
		FName entry = FName(*str);

		T* pRow = data->FindRow<T>(entry, DocumentName);
		if (pRow != nullptr) 
		{
			T t(*pRow);
			arr.Add(t);
		}
	}
	return true;
}

UDataTable* UPSDataManager::GetDataTable(const FString& DocumentName)
{
	FString path = FString::Printf(TEXT("DataTable'/Game/A_Sample/DataDocument/%s.%s'"), *DocumentName, *DocumentName);
			
	static ConstructorHelpers::FObjectFinder<UDataTable> loadData(*path);
	if (!loadData.Succeeded())
	{
		// UE_LOG(LogClass, Log, TEXT("Load Table Data False name %s"), *DocumentName);
		return nullptr;
	}
	
	return loadData.Object;
}



