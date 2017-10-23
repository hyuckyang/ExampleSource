// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotAIController.h"
#include "Robot/Act/RobotActCharacter.h"
#include "Common/PSGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

void ARobotAIController::BeginPlay()
{
	Super::BeginPlay();

	// 등록할 블랙보드 데이터가 없으면 null
	if (m_RobotBBData == nullptr)
	{
		// UE_LOG(LogClass, Log, TEXT("m_RobotBBData nullptr"));
		return;
	}

 	bool bBBSet = UseBlackboard(m_RobotBBData, m_RobotBBComp);
	if (!bBBSet) return;


	
	/*m_RobotCharacter = Cast<ARobotActCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (m_RobotCharacter == nullptr)
	{
		UE_LOG(LogClass, Log, TEXT("m_RobotCharacter nullptr"));
		return;
	}*/
		
	if (m_RobotBHTree == nullptr) return;
	this->RunBehaviorTree(m_RobotBHTree);

	UE_LOG(LogClass, Log, TEXT("RunBehaviorTree ok"));
}

void ARobotAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
}


