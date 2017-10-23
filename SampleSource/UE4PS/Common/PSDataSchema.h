// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PSDataSchema.generated.h"

/**
 * 
 */
UCLASS()
class UE4PS_API UPSDataSchema : public UObject
{
	GENERATED_BODY()

public:
	// ENUM �� ��Ʈ������.
	template<typename T>
	static FORCEINLINE FString GetEnumString(const FString& Name, T value) 
	{
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name);
		if (!enumPtr)
		{
			return FString("None");
		}
		return *(enumPtr ? enumPtr->GetNameStringByIndex(static_cast<uint8>(value)) : "NULL");
	}
};

UENUM(BlueprintType)
enum class eCameraControlID : uint8
{
	FREE = 0,
	TARGET,
	MAX
};


UENUM(BlueprintType)
enum class eHeorControlID : uint8
{
	MANUAL,
	SEMI_AUTO,
	AUTO
};

UENUM(BlueprintType)
enum class eStateID : uint8
{
	NONE = 0,
	IDLE,
	MOVE,
	ATTK,
	DEAD,
	/*TARGET,
	RETURN,*/
};

UENUM(BlueprintType)
enum class eTeamID : uint8
{
	NONE  = 0,
	HERO  = 1,   // 
	ROBOT = 2, //

	// ��ŷ�� ������ �κ�
	// HACKED_ROBOT = HERO,
	MAX = 3
};

UENUM(BlueprintType)
enum class eRobotID : uint8
{
	NONE = 0,
	Robot, // ��������
	RobotTurret, // �ͷ�
	MAX

};

UENUM(BlueprintType) // �̰� �ϴ� ��� ����..
enum class eRootUIID : uint8
{
	None = 0,
	Lobby,
	Field,
};

UENUM(BlueprintType)
enum class eWindowID : uint8
{
	None = 0,
	Field,
};