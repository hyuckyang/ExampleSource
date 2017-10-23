// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RobotAIController.generated.h"

class ARobotActCharacter;
/**
 * 
 */
UCLASS()
class UE4PS_API ARobotAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Black Board ��� / ���� ������ �� Ʈ���� �������Ʈ . ��..
	UPROPERTY(EditAnywhere)
	UBlackboardData* m_RobotBBData;
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* m_RobotBHTree;

protected:
	//
	UBlackboardComponent* m_RobotBBComp;
	ARobotActCharacter*	  m_RobotCharacter;
};
