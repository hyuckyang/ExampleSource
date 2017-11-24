// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreActCharacter.h"
#include "Core/Component/CoreActSightSphereComponent.h"
#include "UMG/Item/ActHudBar.h"
#include "Core/Act/CoreActSight.h"
#include "Common/PSGameInstance.h"
#include "Manager/PSDataManager.h"
#include "Manager/PSActorManager.h"

//
#include "AI/Navigation/NavigationSystem.h"

//
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

//
#include "GameFramework/CharacterMovementComponent.h"


ACoreActCharacter::ACoreActCharacter() /*: Super()*/
{
	PrimaryActorTick.bCanEverTick = true;	

	m_SightComp = CreateDefaultSubobject<UCoreActSightSphereComponent>(TEXT("Sight Component"));
	//m_SightComp->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	m_SightComp->SetupAttachment(RootComponent);
	m_SightComp->bGenerateOverlapEvents = true; // 충돌처리 True

}

void ACoreActCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_PSGameInstance = Cast<UPSGameInstance>(GetWorld()->GetGameInstance());
	m_ActorManager = m_PSGameInstance->GetActorManager();

	this->m_SightDist = 800.f;
	this->m_AttackDist = 125.f;

	//
	/*UClass* bpGC = LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("Blueprint'/Game/A_Sample/Core/BP_CoreActSight.BP_CoreActSight_C'"));
	if (bpGC != nullptr)
	{
		this->m_Sight = this->GetWorld()->SpawnActor<ACoreActSight>(bpGC->GetDefaultObject()->GetClass(), this->GetActorLocation(), this->GetActorRotation());
		this->m_Sight->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		this->m_Sight->SetCharacter(this);
	}*/

	//if (m_SightComp != nullptr)
	m_SightComp->SetCharacter(this);


	//
	params.AddIgnoredActor(this);

	m_SKMesh = FindComponentByClass<USkeletalMeshComponent>();
	if (m_SKMesh == nullptr) { return; }

	m_CHMoveComp = FindComponentByClass<UCharacterMovementComponent>();
	if (m_CHMoveComp == nullptr) { return; }

	//
	m_CHMoveComp->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	// UE_LOG(LogClass, Log, TEXT("ACoreActCharacter Begin Play"));
	
}

void ACoreActCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsValid(m_CurState))
	{
		m_CurState->OnLoop();
	}
	/*if (m_CurState == nullptr) return;
	m_CurState->OnLoop();*/
	

	//
	/*if (this->m_Sight == nullptr) return;
	this->m_Sight->SetActorLocation(this->GetActorLocation());*/
}

void ACoreActCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACoreActCharacter::SetLocalData()
{

	TArray<FCharacterData> arr = m_PSGameInstance->GetDataManager()->GetCharacterData();
	FCharacterData* findData = arr.FindByPredicate([&](FCharacterData data)
	{
		return data.m_ATypeID == m_ActorTypeID;
	});

	if (findData == nullptr) { UE_LOG(LogClass, Log, TEXT("findData == nullptr")); return; }

	m_PointHealth		= findData->m_HeathValue;
	m_PointSpeed		= findData->m_SpeedValue;
	m_PointMeleeAttack	= findData->m_MeleeAttackValue;

	m_CurrentHP			= m_PointHealth;
}

void ACoreActCharacter::AddState(eStateID stateID, UCoreActState * state)
{
	if (state == nullptr) return;

	// 기존 상태가 있다면 삭제 - 다시 등록 함
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

UCoreActState* ACoreActCharacter::FindState(eStateID stateID)
{
	if (!m_StateMap.Contains(stateID)) return nullptr;

	UCoreActState* state = m_StateMap[stateID];

	return IsValid(state) ? state : nullptr;
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
출처 : http://amored8701.tistory.com/132
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

	// 들어오는 액터들은 움직이는 즉 이미 ACoreActCharacter 를 상속 받은 객체들임. 
	return bHit;
}

bool ACoreActCharacter::GetHudSocketLoaction(FVector& locate)
{
	if (m_SKMesh == nullptr) return false;

	FVector head = locate = m_SKMesh->GetSocketLocation(TEXT("head_TargetedPoint"));
	locate = head;

	
	return true;
}

void ACoreActCharacter::SetHeadBar()
{
	if (m_HeadBar == nullptr)
		m_HeadBar = FindComponentByClass<UWidgetComponent>();

	UActHudBar* heabWidget = Cast<UActHudBar>(m_HeadBar->GetUserWidgetObject());
	if (heabWidget != nullptr)
		heabWidget->AddToCharacterInfo(this);
}

void ACoreActCharacter::OnDeathToRagDollActive(FVector bounceDir)
{
	// ??  요소 공부 필요.
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	//


	SetActorEnableCollision(true);

	m_SKMesh->SetAllBodiesSimulatePhysics(true);
	m_SKMesh->SetSimulatePhysics(true);
	m_SKMesh->WakeAllRigidBodies();
	m_SKMesh->bBlendPhysics = true;

	m_SKMesh->SetCollisionProfileName(TEXT("Ragdoll"));

	UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (CharacterComp)
	{
		CharacterComp->StopMovementImmediately();
		CharacterComp->DisableMovement();
		CharacterComp->SetComponentTickEnabled(false);
	}
}

void ACoreActCharacter::OnDeathToParticle()
{
	FVector  locate = GetActorLocation();
	FRotator rotate = GetActorRotation();

	UGameplayStatics::SpawnEmitterAtLocation(this, m_DeathParticle, locate, rotate);
	UGameplayStatics::SpawnSoundAtLocation(this, (USoundBase*)m_DeathSoundCue, locate);
}

//TArray<ACoreActCharacter*> ACoreActCharacter::GetPosibleAttackedActList() 
//{
//	if (m_Sight == nullptr)return nullptr;
//	return m_Sight->GetPossibleAttackActList();
//}