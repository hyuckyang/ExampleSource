// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "RobotActAnimAttackNotifyState.generated.h"


/**
 * 
 */
UCLASS()
class UE4PS_API URobotActAnimAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation);

protected: 
	class ACoreActCharacter* coreAct;

	// 이미 데미지를 준 객체들
	TArray<class ACoreActCharacter*> attackedActList;
};
