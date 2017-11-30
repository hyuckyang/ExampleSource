// Fill out your copyright notice in the Description page of Project Settings.

#include "PSFixedGoalToProtect.h"
#include "Common/PSGameInstance.h"
#include "Robot/Act/RobotActCharacter.h"

// #include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/Engine/Classes/Engine/BlueprintGeneratedClass.h"

/*
*/
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

/*
*/
void APSFixedGoalToProtect::BeginPlay()
{
	Super::BeginPlay();	

	UPSGameInstance* psGameInstance = Cast<UPSGameInstance>(GetGameInstance());
	if (psGameInstance != nullptr)
		psGameInstance->SetToGoalActor(this);

	PatrolPointCreate();

}

/*
*/
void APSFixedGoalToProtect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*
*/
void APSFixedGoalToProtect::OnInColliderBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor,
													 UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweeppResult)
{
	StrikedToDamage(otherActor);
}

/*
*/
void APSFixedGoalToProtect::OnInColliderEndOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
												   int32 otherBodyIndex)
{
	
}

/*
*/
void APSFixedGoalToProtect::StrikedToDamage(AActor* strikeActor)
{
	if (!IsValid(strikeActor))
	{
		UE_LOG(LogClass, Log, TEXT("!IsValid(strikeActor)"));
		return;
	}

	ARobotActCharacter* robotAct = Cast<ARobotActCharacter>(strikeActor);
	if (!IsValid(robotAct)) 
	{
		UE_LOG(LogClass, Log, TEXT("!IsValid(robotAct)"));
		return;
	}

	robotAct->OnDeath();

	// HP
	m_GoalHP--;
	m_goalUpdateDelegate.Broadcast(m_GoalHP, m_GoalTotalHP);
}

/*
후에 XML 데이터로.. 좀 빼자 진짜 뭔 ㅆ 귀찮아서 Healt 하나만 하고 하나도 안해..
*/
void APSFixedGoalToProtect::PatrolPointCreate()
{
	for (int loop = 0, max = 4; loop < max; ++loop) 
	{
		float x, y, z = 0.f;

		float angle = -135.f + (90.f * loop);

		x = GetActorLocation().X + (1100.f * FMath::Cos(FMath::DegreesToRadians(angle)));
		y = GetActorLocation().Y + (1100.f * FMath::Sin(FMath::DegreesToRadians(angle)));
		z = 0.f;

		FHitResult hitResult;
		FCollisionQueryParams params;

		FVector s = FVector(x, y, INT32_MAX);
		FVector e = FVector(x, y, -INT32_MAX);

		bool bHIT = GetWorld()->LineTraceSingleByChannel(hitResult, s, e,
																	ECollisionChannel::ECC_WorldStatic, params);
		/*if (!bHIT)
		{
			UE_LOG(LogClass, Log, TEXT("Continue x %f, y %f, s %f, e %f"), x, y, s.Z, e.Z);
			continue;
		}*/

		/*
		*/
		FActorSpawnParameters spawnParms;
		spawnParms.Owner = GetOwner();

		/*
		*/
		ATargetPoint* targets = GetWorld()->SpawnActor<ATargetPoint>(ATargetPoint::StaticClass(), spawnParms);
		FVector locate = FVector(x, y, hitResult.Location.Z);
		targets->SetActorLocation(locate);

		m_PatrolPoints.Emplace(targets);
	}

	
}

/*
*/
ATargetPoint*  APSFixedGoalToProtect::GetPatrolPointIndex(int32 index)
{
	return m_PatrolPoints.IsValidIndex(index) ? m_PatrolPoints[index] : nullptr;
}

/*
*/
ATargetPoint*  APSFixedGoalToProtect::GetPatrolPointRandom(int32& currentIndex)
{
	int32 rID = 0;

	while (true)
	{
		rID = FMath::RandRange(0, m_PatrolPoints.Num() - 1);
		if (rID != currentIndex) 
		{
			break;
		}
	}
	
	currentIndex = rID;

	UE_LOG(LogClass, Log, TEXT("m_PatrolPoints.rID,  %d currentIndex %d"), rID, currentIndex);
	return m_PatrolPoints.IsValidIndex(currentIndex) ? m_PatrolPoints[currentIndex] : nullptr;
}

