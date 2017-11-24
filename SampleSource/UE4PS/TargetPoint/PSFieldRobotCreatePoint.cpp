// Fill out your copyright notice in the Description page of Project Settings.

#include "PSFieldRobotCreatePoint.h"
#include "Public/TimerManager.h"
#include "Common/PSGameInstance.h"
#include "Manager/PSWidgetManager.h"
#include "Robot/Act/RobotActCharacter.h"
#include "UMG/Window/FieldWindowUWidget.h"

/*
 *
 */
void APSFieldRobotCreatePoint::BeginPlay()
{
	Super::BeginPlay();

	UPSGameInstance* psGameInstance = Cast<UPSGameInstance>(GetGameInstance());
	if (psGameInstance != nullptr)
	{
		psGameInstance->AddToFieldCreatePoint(this);
	}
		
	m_FieldWindow = Cast<UFieldWindowUWidget>(psGameInstance->GetWidgetManager()->GetTopWindow());
}

/*
 *
 */
void APSFieldRobotCreatePoint::CreateRobots(int waveNumber)
{
	m_CreateValue = waveNumber;
	m_CreateCount = 0;

	//UE_LOG(LogClass, Log, TEXT("SetTimer In"));

	SpawnToRobot();
}

/*
 *
 */
void APSFieldRobotCreatePoint::SpawnToRobot()
{
	
	if (m_CreateValue == m_CreateCount) 
	{
		m_WaveTimeHandle.Invalidate();
		GetWorldTimerManager().ClearTimer(m_WaveTimeHandle);

		UE_LOG(LogClass, Log, TEXT("SpawnToRobot End"));
		return;
	}

	FString toPath = FString::Printf(TEXT("Blueprint'/Game/A_Sample/Robot/BP_RobotActCharacter.BP_RobotActCharacter_C'"));
	UClass* bpGC = LoadObject<UBlueprintGeneratedClass>(nullptr, *toPath);

	if (bpGC != nullptr)
	{
		ARobotActCharacter* robot = GetWorld()->SpawnActor<ARobotActCharacter>(bpGC, GetActorLocation(), GetActorRotation());
	}

	GetWorldTimerManager().SetTimer(m_WaveTimeHandle, this, &APSFieldRobotCreatePoint::SpawnToRobot, 0.8f, false);
	m_CreateCount++;
}


//void APSFieldRobotCreatePoint::testcreatefunc()
//{
//	CreateRobots();
//}
