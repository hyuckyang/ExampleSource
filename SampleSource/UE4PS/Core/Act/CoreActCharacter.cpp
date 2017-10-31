// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreActCharacter.h"
#include "Core/Act/CoreActSight.h"
#include "Common/PSGameInstance.h"
#include "Manager/PSActorManager.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACoreActCharacter::ACoreActCharacter()
{
	PrimaryActorTick.bCanEverTick = true;	

	//m_SKMesh = 
}

void ACoreActCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_PSGameInstance = Cast<UPSGameInstance>(GetWorld()->GetGameInstance());
	m_ActorManager = m_PSGameInstance->GetActorManager();

	this->m_SightDist = 800.f;
	this->m_AttackDist = 125.f;

	//
	UClass* bpGC = LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("Blueprint'/Game/A_Sample/Core/BP_CoreActSight.BP_CoreActSight_C'"));
	if (bpGC != nullptr)
	{
		this->m_Sight = this->GetWorld()->SpawnActor<ACoreActSight>(bpGC->GetDefaultObject()->GetClass(), this->GetActorLocation(), this->GetActorRotation());
		this->m_Sight->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		this->m_Sight->SetCharacter(this);
	}

	//
	params.AddIgnoredActor(this);

	m_SKMesh = FindComponentByClass<USkeletalMeshComponent>();
	if (m_SKMesh == nullptr) { return; }

	m_CHMoveComp = FindComponentByClass<UCharacterMovementComponent>();
	if (m_CHMoveComp == nullptr) { return; }

	//
	m_CHMoveComp->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	
}

void ACoreActCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (this->m_CurState == nullptr) return;
	this->m_CurState->OnLoop();

	//
	if (this->m_Sight == nullptr) return;
	this->m_Sight->SetActorLocation(this->GetActorLocation());
}

void ACoreActCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACoreActCharacter::AddState(eStateID stateID, UCoreActState * state)
{
	if (state == nullptr) return;

	// ���� ���°� �ִٸ� ���� - �ٽ� ��� ��
	if (this->m_StateMap.Contains(stateID)) 
	{
		this->m_StateMap.Remove(stateID);
	}

	m_StateMap.Add(stateID, state);

	m_StateMap[stateID]->SetPSGameInstance(m_PSGameInstance);
	m_StateMap[stateID]->SetCharacter(this);
	m_StateMap[stateID]->SetStateID(stateID);
}

void ACoreActCharacter::ChangeState(eStateID stateID, void* arg1 /*= nullptr*/, void* arg2 /*= nullptr*/)
{

}

UCoreActState * ACoreActCharacter::FindState(eStateID stateID)
{
	return this->m_StateMap.Contains(stateID) == true ? m_StateMap[stateID] : nullptr;
}

void ACoreActCharacter::OnUpdateToLocateWithNavi(FVector locate)
{
	//
	UNavigationSystem* naviSys = GetWorld()->GetNavigationSystem();
	if (naviSys == nullptr) return;

	//
	// this->m_MoveLocate = locate;
	//

	naviSys->SimpleMoveToLocation(this->GetController(), locate);
}

void ACoreActCharacter::OnUpdateToRocate(float rotateSpeed)
{

}

/*
��ó : http://amored8701.tistory.com/132
*/
bool ACoreActCharacter::IsInAngle(AActor* target, float angle)
{
	FVector locate = FVector(this->GetActorLocation().X, this->GetActorLocation().Y, 0.f);
	FVector end	= FVector(target->GetActorLocation().X, target->GetActorLocation().Y, 0.f);
	//FVector dir = (end - locate).SafeNormal();
	FVector dir = (end - locate).GetSafeNormal();

	// float dot = FVector::DotProduct(this->GetActorForwardVector(), dir.SafeNormal());
	float dot = FVector::DotProduct(this->GetActorForwardVector(), dir.GetSafeNormal());
	float acosAngle = FMath::Acos(dot);
	float degree = FMath::RadiansToDegrees(acosAngle);
	float turnDegree = 0.f;

	FVector cross = FVector::CrossProduct(this->GetActorForwardVector(), dir);
	if (cross.Z > 0)
	{
		turnDegree = degree;
	}
	else if (cross.Z < 0)
	{
		turnDegree = -degree;
	}

	if (-angle / 2 <= turnDegree && turnDegree <= angle / 2)
	{
		return true;
	}
	return false;
}

bool ACoreActCharacter::IsInSight(AActor * actors)
{
	
	FHitResult hit;
	FVector locate = this->GetActorLocation();
	FVector target = actors->GetActorLocation();
	bool bHit = GetWorld()->LineTraceSingleByChannel(hit, locate, target, ECollisionChannel::ECC_WorldDynamic, params);

	// ������ ���͵��� �����̴� �� �̹� ACoreActCharacter �� ��� ���� ��ü����. 
	return bHit;
}

bool ACoreActCharacter::GetHudSocketLoaction(FVector& locate)
{
	if (m_SKMesh == nullptr) return false;

	//locate = m_SKMesh->GetSocketLocation(TEXT("head_TargetedPoint"));
	locate = GetActorLocation();
	//UE_LOG(LogClass, Log, TEXT("OnTickBPGetActorLocation locate X, %f, locate Y, %f locate Z, %f"), locate.X, locate.Y, locate.Z);
	return true;
}

