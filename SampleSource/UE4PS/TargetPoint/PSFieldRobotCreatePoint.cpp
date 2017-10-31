// Fill out your copyright notice in the Description page of Project Settings.

#include "PSFieldRobotCreatePoint.h"
#include "Common/PSGameInstance.h"
#include "Robot/Act/RobotActCharacter.h"

/*
*/
void APSFieldRobotCreatePoint::BeginPlay()
{
	Super::BeginPlay();

	UPSGameInstance* psGameInstance = Cast<UPSGameInstance>(GetGameInstance());
	if (psGameInstance != nullptr)
	{
		UE_LOG(LogClass, Log, TEXT("AddToFieldCreatePoint"));
		psGameInstance->AddToFieldCreatePoint(this);
	}
		

	//CreateRobots();
	//GetWorldTimerManager().SetTimer(inoutHandle, this, &APSFieldRobotCreatePoint::testcreatefunc, 0.1f, false, 2.f);
}

/*
*/
void APSFieldRobotCreatePoint::CreateRobots(int waveNumber)
{

	// юс╫ц 
	
	FString toPath = FString::Printf(TEXT("Blueprint'/Game/A_Sample/Robot/BP_RobotActCharacter.BP_RobotActCharacter_C'"));
	UClass* bpGC = LoadObject<UBlueprintGeneratedClass>(nullptr, *toPath);

	if (bpGC != nullptr)
	{
		GetWorld()->SpawnActor<ARobotActCharacter>(bpGC, GetActorLocation(), GetActorRotation());

		//ARobotActCharacter* robot = GetWorld()->SpawnActor<ARobotActCharacter>(bpGC, GetActorLocation(), GetActorRotation());
	}
	
}

//void APSFieldRobotCreatePoint::testcreatefunc()
//{
//	CreateRobots();
//}
