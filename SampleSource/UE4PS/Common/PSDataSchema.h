// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
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
enum class eStateKindOfID : uint8
{
	LOWER = 0,
	UPPER,
};

UENUM(BlueprintType)
enum class eStateID : uint8
{
	NONE = 0,

	/*
	Lower
	*/
	IDLE,
	MOVE,
	TARGET,
	RETURN,

	/*
	Upper
	*/
	ATTK,
	//ATTK_SHOOT,

	/*
	Unique
	*/
	PATROL, // 순찰 - Hero AI

	DEATH, // 
	SLEEP, // 게임 끝났을 때
	MAX,
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
	RL2A2, // 이족보행
	RL4B1, // 터렛
	MAX

};

UENUM(BlueprintType)
enum class eWeaponTriggerID : uint8
{
	NONE = 0,
	SEMIAUTO,
	BURST,
	FULLAUTO,
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
	End,
};

UENUM(BlueprintType)
enum class eWaveTypeID : uint8
{
	STANDBY = 0,
	UPDATE, // Tick
	BREAK, // 휴식
	END,  // 웨이브 끝( 전체 끝임 )

};


/**
 *
 */
USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FCharacterData()
		:	m_ATypeID(eActorTypeID::NONE),
			m_RTypeID(eRobotID::NONE),
			m_HeathValue(0), m_SpeedValue(0), m_MeleeAttackValue(0)
			{};

	FCharacterData(FCharacterData* data)
	{
		m_ATypeID = data->m_ATypeID;
		m_RTypeID = data->m_RTypeID;
		m_HeathValue = data->m_HeathValue;
		m_SpeedValue = data->m_SpeedValue;
		m_MeleeAttackValue = data->m_MeleeAttackValue;
	};

	UPROPERTY(EditAnywhere)
		eActorTypeID	m_ATypeID;
	UPROPERTY(EditAnywhere)
		eRobotID		m_RTypeID;
	UPROPERTY(EditAnywhere)
		int32			m_HeathValue;
	UPROPERTY(EditAnywhere)
		int32			m_SpeedValue;
	UPROPERTY(EditAnywhere)
		int32			m_MeleeAttackValue;
};