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
	// ENUM 을 스트링으로.
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
	DEATH,
	TARGET,
	RETURN,
};

UENUM(BlueprintType)
enum class eActorTypeID : uint8
{
	NONE  = 0,
	HERO  = 1,   // 
	ROBOT = 2, //

	// 해킹된 상태의 로봇
	// HACKED_ROBOT = HERO,
	MAX = 3
};

UENUM(BlueprintType)
enum class eTeamID : uint8
{
	NONE = 0,
	BLUE,
	DARK,
};

UENUM(BlueprintType)
enum class eRobotID : uint8
{
	NONE = 0,
	Robot, // 이족보행
	RobotTurret, // 터렛
	MAX

};

UENUM(BlueprintType) // 이거 일단 사용 안함..
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