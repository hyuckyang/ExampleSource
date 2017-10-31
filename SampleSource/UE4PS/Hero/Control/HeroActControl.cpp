// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroActControl.h"
#include "Common/PSDataSchema.h"
#include "Manager/PSActorManager.h"
#include "Manager/PSWidgetManager.h"
#include "Hero/Act/HeroActCharacter.h"
#include "UMG/Window/FieldWindowUWidget.h"

/*

*/
AHeroActControl::AHeroActControl() : Super()
{
	m_DecalToCursur = CreateDefaultSubobject<UDecalComponent>("TargetToDecal");
	m_DecalToCursur->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> CursurDecalMatAsset(TEXT("Material'/Game/A_Sample/Core/M_TargetPoint.M_TargetPoint'"));
	if (CursurDecalMatAsset.Succeeded()) m_DecalToCursur->SetDecalMaterial(CursurDecalMatAsset.Object);
	//m_DecalToCursur->setsca

	m_DecalToCursur->DecalSize = FVector(16.0f, 32.0f, 32.0f);
}

/*

*/
void AHeroActControl::BeginPlay() 
{
	Super::BeginPlay();

	if (GetTargetHero() == nullptr) return;

	//
	m_ControlID = eCameraControlID::TARGET;
	
	// 
	m_TargetLocation = GetTargetHero()->GetActorLocation();
	this->OnMoveForward(1.f); this->OnMoveRight(1.f);


	m_FieldWindow = Cast<UFieldWindowUWidget>(m_WidgetManager->GetTopWindow());
}

/*

*/
void AHeroActControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_ControlID == eCameraControlID::TARGET) 
	{
		if (GetTargetHero() == nullptr) 
		{
			// Ÿ���� ������ �׳� ��Ʈ�� Ÿ���� ������ �ѱ�
			m_ControlID = eCameraControlID::FREE;
			return;
		}
		FVector currentLocation = this->GetActorLocation();
		FVector targetLocation	= this->m_ActorManager->GetControlHeroActor()->GetActorLocation();
		m_TargetLocation = FMath::VInterpTo(currentLocation, targetLocation, DeltaTime, 20.f);

		this->OnMoveForward(DeltaTime); this->OnMoveRight(DeltaTime);

		FHitResult TraceResult(ForceInit);
		this->m_pController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);

		FRotator rotator = FRotationMatrix::MakeFromX(TraceResult.Location - GetTargetHero()->GetActorLocation()).Rotator();
		this->GetTargetHero()->SetActorRotation(FRotator(0.f, rotator.Yaw, 0.f));
	}

	// TEST TARGET
	FHitResult TraceHitResult;
	this->m_pController->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
	FVector CursorFV = TraceHitResult.ImpactNormal;
	FRotator CursorR = CursorFV.Rotation();
	m_DecalToCursur->SetWorldLocation(TraceHitResult.Location);
	m_DecalToCursur->SetWorldRotation(CursorR);

}

/*

*/
void AHeroActControl::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	this->InputComponent->BindAction("MouseWheelUp",	IE_Pressed,  this, &AHeroActControl::InputMouseWheelUp);
	this->InputComponent->BindAction("MouseWheelDown",	IE_Pressed,  this, &AHeroActControl::InputMouseWheelDown);
	this->InputComponent->BindAction("MouseLClick",		IE_Pressed,  this, &AHeroActControl::InputMouseLClickPressed);
	this->InputComponent->BindAction("MouseLClick",		IE_Released, this, &AHeroActControl::InputMouseLClickReleased);
	this->InputComponent->BindAction("MouseRClick",		IE_Pressed,  this, &AHeroActControl::InputMouseRClickPressed);
	this->InputComponent->BindAction("MouseRClick",		IE_Released, this, &AHeroActControl::InputMouseRClickReleased);
	this->InputComponent->BindAction("TapToNext",		IE_Released, this, &AHeroActControl::InputTapClickReleased);
	this->InputComponent->BindAction("SpaceToTarget",	IE_Released, this,  &AHeroActControl::InputSpaceClickReleased);

	this->InputComponent->BindAxis("MouseX",		this, &AHeroActControl::InputMouseX);
	this->InputComponent->BindAxis("MouseY",		this, &AHeroActControl::InputMouseY);
	this->InputComponent->BindAxis("MoveForward",	this, &AHeroActControl::InputKeyBoardForward);
	this->InputComponent->BindAxis("MoveRight",		this, &AHeroActControl::InputKeyBoardRight);
}

#pragma region Input Action
void AHeroActControl::InputMouseWheelUp()
{
	this->OnZoomIn();
}

void AHeroActControl::InputMouseWheelDown()
{
	this->OnZoomOut();
}

void AHeroActControl::InputMouseLClickPressed()
{
	if (m_ControlID == eCameraControlID::FREE) 
	{
		FHitResult hitresult;
		m_pController->GetHitResultUnderCursor(ECC_Visibility, false, hitresult);

		GetTargetHero()->OnUpdateToLocateWithNavi(hitresult.ImpactPoint);
	}

}

void AHeroActControl::InputMouseLClickReleased()
{
	/*if (m_ControlID == eCameraControlID::FREE)
	{

	}*/

	if (GetTargetHero() == nullptr) return;

	GetTargetHero()->OnFire();
	
	
}

void AHeroActControl::InputMouseRClickPressed()
{
	if (m_ControlID == eCameraControlID::FREE) { this->m_bRotateCam = true; return; }
	//	
	if (m_ControlID == eCameraControlID::TARGET)
	{

		return;
	}
}

void AHeroActControl::InputMouseRClickReleased()
{
	if (m_ControlID == eCameraControlID::FREE) { this->m_bRotateCam = false; return; }
	//	
	if (m_ControlID == eCameraControlID::TARGET)
	{
		return;
	}
}

void AHeroActControl::InputTapClickReleased()
{
	/*if (m_ControlID == eCameraControlID::FREE) 
	{
		return;
	}

	if (m_ControlID == eCameraControlID::TARGET)
	{
		return;
	}*/

	SetHeroSelected(m_ActorManager->GetTapToHeroActor());
}

void AHeroActControl::InputSpaceClickReleased() 
{
	this->SetControlTypeSwap();
}
#pragma endregion


#pragma region Input Axis
void AHeroActControl::InputKeyBoardForward(float deltaTick)
{


	if (m_ControlID == eCameraControlID::FREE) { this->m_TargetLocation = this->GetActorLocation(); OnMoveForward(deltaTick); return; }
	//	
	if (m_ControlID == eCameraControlID::TARGET) 
	{
		GetTargetHero()->SetMoveForward(deltaTick);

		//FVector dir = FRotationMatrix(m_pCamera->GetComponentRotation()).GetScaledAxis(EAxis::X);
		FVector dir = FRotationMatrix(GetTargetHero()->GetActorRotation()).GetScaledAxis(EAxis::X);
		GetTargetHero()->AddMovementInput(dir, deltaTick * 20.f);

		// �̵� ���°� �Ǿ�� ��
		//GetTargetHero()->ChangeState(eStateID::MOVE);
	}
	
}

void AHeroActControl::InputKeyBoardRight(float deltaTick)
{

	if (m_ControlID == eCameraControlID::FREE) { this->m_TargetLocation = this->GetActorLocation(); OnMoveRight(deltaTick); return;	}
	//
	if (m_ControlID == eCameraControlID::TARGET)
	{
		GetTargetHero()->SetMoveRight(deltaTick);

		//FVector dir = FRotationMatrix(m_pCamera->GetComponentRotation()).GetScaledAxis(EAxis::Y);
		FVector dir = FRotationMatrix(GetTargetHero()->GetActorRotation()).GetScaledAxis(EAxis::Y);
		GetTargetHero()->AddMovementInput(dir, deltaTick * 20.f);

		// �̵� ���°� �Ǿ�� ��
		//GetTargetHero()->ChangeState(eStateID::MOVE);
	}
	
}

void AHeroActControl::InputMouseX(float deltaTick)
{
	if (deltaTick == 0.f) return;
	if (m_ControlID == eCameraControlID::FREE) { this->m_TargetLocation = this->GetActorLocation(); OnRotatePitch(deltaTick); return; }
	//	
	if (m_ControlID == eCameraControlID::TARGET) { }
}

void AHeroActControl::InputMouseY(float deltaTick)
{
	if (deltaTick == 0.f) return;
	if (m_ControlID == eCameraControlID::FREE) { this->m_TargetLocation = this->GetActorLocation(); OnRotateYaw(deltaTick); return; }
	//	
	if (m_ControlID == eCameraControlID::TARGET) { }
}
#pragma endregion


/*

*/
void AHeroActControl::SetControlTypeSwap()
{
	int cur = (int)m_ControlID;
	int max = (int)eCameraControlID::MAX;

	if (cur + 1 >= max) 
	{
		m_ControlID = eCameraControlID::FREE;
	}
	else
	{
		m_ControlID = (eCameraControlID)(cur + 1);
	}

	SetHeroSelected(this->GetTargetHero());

	//  UI ������Ʈ
	if (m_FieldWindow == nullptr)
	{
		m_FieldWindow = Cast<UFieldWindowUWidget>(m_WidgetManager->GetTopWindow());
	}
	
	m_FieldWindow->SetToControlMode(GetCameraControlID());

}


/*

*/
AHeroActCharacter* AHeroActControl::GetTargetHero() 
{ 
	return m_ActorManager != nullptr && m_ActorManager->GetControlHeroActor() ? m_ActorManager->GetControlHeroActor() : nullptr; 
}

/*

*/
void AHeroActControl::SetHeroSelected(AHeroActCharacter* hero)
{
	if (GetTargetHero() != nullptr) 
	{
		GetTargetHero()->SetHeroControlID(eHeorControlID::AUTO);
		GetTargetHero()->SetSelected(false);
	}

	eHeorControlID heroControl = m_ControlID == eCameraControlID::TARGET ?
															eHeorControlID::MANUAL : eHeorControlID::SEMI_AUTO;

	if (heroControl == eHeorControlID::MANUAL)
	{
		m_TargetLocation = GetTargetHero()->GetActorLocation();
		this->OnMoveForward(1.f); this->OnMoveRight(1.f);
	}

	m_ActorManager->SetControlHeroActor(hero);
	hero->SetHeroControlID(heroControl);
	hero->SetSelected(true);

	//  UI ������Ʈ
	if (m_FieldWindow == nullptr)
	{
		m_FieldWindow = Cast<UFieldWindowUWidget>(m_WidgetManager->GetTopWindow());
	}
	m_FieldWindow->SelectToHeroInfo(hero->GetUniqueID());
}