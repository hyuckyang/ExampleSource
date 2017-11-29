// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroActCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Manager/PSActorManager.h"
#include "Hero/Weapon/HeroGunWeapon.h"
#include "Hero/Act/HeroActState.h"
#include "Hero/AI/HeroAIController.h"
#include "Core/Act/CoreActSight.h"
#include "Core/Component/CoreActSightSphereComponent.h"
/*
*/
#include "Runtime/Engine/Classes/Engine/BlueprintGeneratedClass.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"

/*
애니메이션
*/
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"

AHeroActCharacter::AHeroActCharacter() : Super()
{
	// Weapon -- 
	/*static ConstructorHelpers::FClassFinder<UClass> heroWeapon(TEXT("Blueprint'/Game/A_Sample/Hero/Weapon/BP_HeroGunWeapon.BP_HeroGunWeapon_C'"));
	if (heroWeapon.Succeeded() == false) { UE_LOG(LogClass, Log, TEXT("heroWeapon not Find"));  return; }*/

	/*static ConstructorHelpers::FObjectFinder<UBlueprint> heroWeapon(TEXT("Blueprint'/Game/A_Sample/Hero/Weapon/BP_HeroGunWeapon.BP_HeroGunWeapon'"));;
	if (heroWeapon.Succeeded() == false) { UE_LOG(LogClass, Log, TEXT("heroWeapon not Find"));  return; }*/
}

void AHeroActCharacter::BeginPlay()
{
	Super::BeginPlay();
	m_ActorManager->AddToHero(this);
	
	m_ActorTypeID	= eActorTypeID::HERO;
	m_ControlID		= eHeorControlID::AUTO;
	m_TeamID		= eTeamID::BLUE;
	
	m_AttackDist = 500.f;
	m_SightDist  = 800.f;
	m_SightComp->SetSightDistance(m_SightDist);
	/*m_Sight->SetSightDistance(m_SightDist);*/

	m_HAIController = Cast<AHeroAIController>(GetController());
	

	RandomCustomizing();
	RandomNames();

	SetHeadBar();
	SetLocalData();
	//
	// USkeletalMeshComponent* skel = FindComponentByClass<USkeletalMeshComponent>();
	//

	m_PointSMMesh = FindComponentByClass<UStaticMeshComponent>();
	if (m_PointSMMesh != nullptr) m_PointSMMesh->SetVisibility(false);


	UClass* bpGC	= LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("Blueprint'/Game/A_Sample/Hero/Weapon/BP_HeroGunWeapon.BP_HeroGunWeapon_C'"));
	m_GunWeapon		= this->GetWorld()->SpawnActor<AHeroGunWeapon>(bpGC->GetDefaultObject()->GetClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	m_GunWeapon		->AttachRootComponentTo(m_SKMesh, FName(TEXT("rHandGripPoint")));
	m_GunWeapon		->SetActorRotation(GetActorRotation());
	m_GunWeapon		->SetCoreCharcter(this);

	AddState(eStateID::IDLE,	NewObject<UHeroActIdleState>());
	AddState(eStateID::MOVE,	NewObject<UHeroActMoveState>());
	AddState(eStateID::PATROL,	NewObject<UHeroActPatrolState>());
	AddState(eStateID::TARGET,	NewObject<UHeroActTargetState>());
	AddState(eStateID::ATTK,	NewObject<UHeroActAttackState>());

	SetHeroControlID(m_ControlID);
	//ChangeState(eStateID::IDLE);
	
}

void AHeroActCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	/*if (m_SKMesh != nullptr) 
	{
		FVector hudLocate; 
		GetHudSocketLoaction(hudLocate);
		m_DecalToTarget->SetWorldLocation(hudLocate);
	}*/
	
	//FVector vec3 = this->GetActorLocation();
	
}

void AHeroActCharacter::AddState(eStateID stateID, UCoreActState* state)
{
	Super::AddState(stateID, state);
}

void AHeroActCharacter::ChangeState(eStateID stateID, void* arg1, void* arg2)
{
	Super::ChangeState(stateID, arg1, arg2);

	UCoreActState* state = FindState(stateID);
	if (state == nullptr) return;

	eStateID oldState = eStateID::NONE;
	if (m_CurState != nullptr) 
	{
		// 어느 상태로 가는지 알려줌
		oldState = m_CurState->GetStateID();
		m_CurState->OnExit(stateID);
	}
	
	m_CurState = state;
	m_CurState->OnExecute(oldState, arg1, arg2);

	// AI 동기화.
	if (m_HAIController != nullptr) 
	{
		m_HAIController->SetChangeStateID(stateID);
	}
}

void AHeroActCharacter::SetHeroControlID(eHeorControlID controlID) 
{
	AHeroAIController* heroAI = Cast<AHeroAIController>(AIControllerClass);

	switch (controlID)
	{
	case eHeorControlID::MANUAL:
	case eHeorControlID::SEMI_AUTO :
		m_HAIController->StopBehaviorTree();

		ChangeState(eStateID::IDLE);
		break;
	default:
		m_HAIController->StartBehaviorTree(this);

		// 임시 함수.
		ChangeState(eStateID::PATROL);
		break;
	}
	m_ControlID = controlID;
}

/*
..
*/
void AHeroActCharacter::SetSelected(bool bVisible)
{
	if (m_PointSMMesh == nullptr) return;
	m_PointSMMesh->SetVisibility(bVisible, true);
}

/*
.. 
*/
void AHeroActCharacter::RandomCustomizing()
{
	// 
}

/*
..
*/
void AHeroActCharacter::RandomNames()
{
	for (int loop = 0, max = 5; loop < max; ++loop)
	{
		int rAscii = FMath::RandRange(65, 90);
		char convert = (char)rAscii;
		m_HeroName.AppendChar(convert);
	}
}

/*
..
*/
void AHeroActCharacter::OnFire(bool bCanFire)
{
	if (m_GunWeapon == nullptr)return;

	PlayAnimMontage(m_HeroRifleOneShootMontage);

	m_GunWeapon->OnFire(bCanFire);

}

/*
..
*/
eWeaponTriggerID AHeroActCharacter::GetWeaponTriggerID()
{
	return m_GunWeapon == nullptr ? m_GunWeapon->GetWTriggerID() : eWeaponTriggerID::SEMIAUTO;
}

/*
..
*/
void AHeroActCharacter::OnWeaponTriggerSwitcher()
{
	if (!IsValid(m_GunWeapon)) return;

	m_GunWeapon->SetTriggerSwitch();

	m_switcherWTriggerDele.ExecuteIfBound(m_GunWeapon->GetWTriggerID());
}