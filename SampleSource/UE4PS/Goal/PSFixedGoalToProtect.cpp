// Fill out your copyright notice in the Description page of Project Settings.

#include "PSFixedGoalToProtect.h"
#include "Common/PSGameInstance.h"
#include "Robot/Act/RobotActCharacter.h"
APSFixedGoalToProtect::APSFixedGoalToProtect()
{
 	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));

	m_BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	// m_BoxComp->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	m_BoxComp->SetupAttachment(RootComponent);
	m_BoxComp->bGenerateOverlapEvents = true; // 충돌처리 True

	m_BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APSFixedGoalToProtect::OnInColliderBeginOverlap);
	m_BoxComp->OnComponentEndOverlap.AddDynamic(this, &APSFixedGoalToProtect::OnInColliderEndOverlap);
}

void APSFixedGoalToProtect::BeginPlay()
{
	Super::BeginPlay();	

	UPSGameInstance* psGameInstance = Cast<UPSGameInstance>(GetGameInstance());
	if (psGameInstance != nullptr)
		psGameInstance->SetToGoalActor(this);

	// UE_LOG(LogClass, Log, TEXT("APSFixedGoalToProtect Begin Play"));
}

void APSFixedGoalToProtect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APSFixedGoalToProtect::OnInColliderBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor,
													 UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweeppResult)
{
	if (!IsValid(otherActor)) return;
	
	ARobotActCharacter* robotAct = Cast<ARobotActCharacter>(otherActor);
	if (!IsValid(robotAct)) return;

	
	robotAct->OnDeath();
	

	// HP
	m_GoalHP--;
	m_goalUpdateDelegate.Broadcast(m_GoalHP, m_GoalTotalHP);
}

void APSFixedGoalToProtect::OnInColliderEndOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
												   int32 otherBodyIndex)
{
	
}