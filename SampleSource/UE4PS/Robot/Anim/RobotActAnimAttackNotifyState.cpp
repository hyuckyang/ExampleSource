// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotActAnimAttackNotifyState.h"
#include "Core/Act/CoreActCharacter.h"
#include "Core/Act/CoreActSight.h"
#include "Core/Component/CoreActSightSphereComponent.h"
#include "Components/SkeletalMeshComponent.h"


void URobotActAnimAttackNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);


	if (coreAct == nullptr)
		coreAct = Cast<ACoreActCharacter>(MeshComp->GetOwner());

	attackedActList.Empty();

}

void URobotActAnimAttackNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);


	if (coreAct == nullptr)	return;
	if (coreAct->m_SightComp == nullptr) return;

	// 아래 크래쉬 원인 찾는 중
	// return;
	

	if (coreAct->m_SightComp->IsAttackCharacter() == false) return;

	TArray<ACoreActCharacter*> attackAct = coreAct->m_SightComp->GetPossibleAttackActList();

	for (int loop = 0, max = attackAct.Num(); loop < max; loop++) 
	{
		if (!attackedActList.Contains(attackAct[loop]))
		{
			attackAct[loop]->ReceivedAttackDamage(1);

			attackedActList.Emplace(attackAct[loop]);
		}

		//UE_LOG(LogClass, Log, TEXT("attackActs"));
	}
	
}

void URobotActAnimAttackNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

}
