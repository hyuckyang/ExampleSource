// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroActCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/DecalComponent.h"
#include "Manager/PSActorManager.h"
#include "Hero/Act/HeroActState.h"
#include "Materials/Material.h"

AHeroActCharacter::AHeroActCharacter() :Super()
{
	/*m_CursurToDecal = CreateDefaultSubobject<UDecalComponent>("CursurToDecal");
	m_CursurToDecal->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> CursurDecalMatAsset(TEXT("Material'/Game/A_Sample/Core/M_CursorPoint.M_CursorPoint'"));
	if (CursurDecalMatAsset.Succeeded()) m_CursurToDecal->SetDecalMaterial(CursurDecalMatAsset.Object);*/
	//m_TargetToDecal = CreateDefaultSubobject<UDecalComponent>("TargetToDecal");
	//m_TargetToDecal->SetupAttachment(RootComponent/*, FName("head_TargetedPoint")*/);
	//static ConstructorHelpers::FObjectFinder<UMaterial> TargetDecalMatAsset(TEXT("Material'/Game/A_Sample/Core/M_TargetPoint.M_TargetPoint'"));
	//if (TargetDecalMatAsset.Succeeded()) m_TargetToDecal->SetDecalMaterial(TargetDecalMatAsset.Object);
	//m_TargetToDecal->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	//m_TargetToDecal->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	//FindComponentByClass<USkeletalMeshComponent>()
	
}



void AHeroActCharacter::BeginPlay()
{
	Super::BeginPlay();
	m_ActorManager->AddToHero(this);
	
	m_TeamID	= eTeamID::HERO;
	m_ControlID = eHeorControlID::AUTO;
	
	m_SightDist = 200.f;

	this->RandomCustomizing();
	this->RandomNames();

	//
	// USkeletalMeshComponent* skel = FindComponentByClass<USkeletalMeshComponent>();
	//

	//m_TargetToDecal->SetWorldLocation(USceneComponent::GetSocketLocation(""));

	this->AddState(eStateID::IDLE, NewObject<UHeroActIdleState>());
	this->AddState(eStateID::MOVE, NewObject<UHeroActMoveState>());

	this->ChangeState(eStateID::IDLE);
	
}

void AHeroActCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector vec3 = this->GetActorLocation();
	
}

void AHeroActCharacter::AddState(eStateID stateID, UCoreActState* state)
{
	Super::AddState(stateID, state);
}

void AHeroActCharacter::ChangeState(eStateID stateID, void* arg1, void* arg2)
{
	Super::ChangeState(stateID, arg1, arg2);

	UCoreActState* state = this->FindState(stateID);
	if (state == nullptr) return;

	eStateID oldState = eStateID::NONE;
	if (this->m_CurState != nullptr) 
	{
		// 어느 상태로 가는지 알려줌
		oldState = m_CurState->GetStateID();
		this->m_CurState->OnExit(stateID);
	}
	
	this->m_CurState = state;
	this->m_CurState->OnExecute(oldState, arg1, arg2);
}

void AHeroActCharacter::SetHeroControlID(eHeorControlID controlID) 
{
	if (controlID == eHeorControlID::MANUAL) 
	{
		// 직접 조작 시 상태를 아이들로 바꾼다.
		ChangeState(eStateID::IDLE);
	}
	m_ControlID = controlID;

	
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

