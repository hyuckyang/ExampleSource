// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreCameraControl.h"
#include "Common/PSGameInstance.h"
#include "Manager/PSActorManager.h"
#include "Manager/PSWidgetManager.h"

ACoreCameraControl::ACoreCameraControl() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	this->m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("pCamera"));
	this->m_pCamera->SetupAttachment(RootComponent);
	// this->m_pCamera->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}

void ACoreCameraControl::BeginPlay()
{
	Super::BeginPlay();

	// ���콺 Ŀ���� �����ݴϴ�.
	this->m_pController = GetWorld()->GetFirstPlayerController();
	this->m_pController->bShowMouseCursor = true;

	// �Ŵ��� ����.
	m_PSGameInstance = Cast<UPSGameInstance>(GetWorld()->GetGameInstance());
	m_PSGameInstance->SetCameraControlActor(this);
	m_ActorManager	= m_PSGameInstance->GetActorManager();
	m_WidgetManager = m_PSGameInstance->GetWidgetManager();
	//  
	// m_ControlID = eCameraControlID::TARGET;

	this->InitCameraParameter();
	//
	this->OnUpdateLocateAndRotate();
	
}

void ACoreCameraControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// m_TargetLocation = this->GetActorLocation();
}

void ACoreCameraControl::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/*
ī�޶� �Ķ���� �ʱ�ȭ
*/
void ACoreCameraControl::InitCameraParameter()
{
	// ���� ����Ʈ�� �Ķ���� ���� �״�� �����Խ��ϴ�.
	this->m_bRotateCam = false;
	this->m_fCamDistMin = 256.f;
	this->m_fCamDistMax = 1024.f;
	this->m_fCamDist = 637.f;
	this->m_fCamPitch = 20.f;
	this->m_fCamYaw = 0.f;

	//
	this->m_fLocateSpeed = 5.f;
	this->m_fRotateSpeed = 2.f;
	this->m_fZoomSpeed = 15.f;
}

FVector ACoreCameraControl::GetPointViewVector(float dist, float pitch, float yaw)
{
	float x, y, z = 0.f;
	x = dist * FMath::Cos(FMath::DegreesToRadians(yaw)) * FMath::Sin(FMath::DegreesToRadians(pitch));
	y = dist * FMath::Sin(FMath::DegreesToRadians(yaw)) * FMath::Sin(FMath::DegreesToRadians(pitch));
	z = dist * FMath::Cos(FMath::DegreesToRadians(pitch));
	FVector vec3 = FVector(x, y, z);
	return vec3;
}

FVector ACoreCameraControl::GetAddVec3ToLocate(FVector vec3, float amount)
{
	return (vec3 * amount) + m_TargetLocation; // this->GetActorLocation();
}

FRotator ACoreCameraControl::GetIsolateYaw(FRotator rotator)
{
	return FRotator(0.f, rotator.Yaw, 0.f);
}

void ACoreCameraControl::OnUpdateLocateAndRotate()
{
	//
	FVector locate = this->GetPointViewVector(m_fCamDist, m_fCamPitch, m_fCamYaw);
	this->m_pCamera->SetRelativeLocation(locate);
	//
	FRotator rotator = FRotationMatrix::MakeFromX(FVector::ZeroVector - this->m_pCamera->RelativeLocation).Rotator();
	this->m_pCamera->SetRelativeRotation(rotator);
}

#pragma region Free Functions
/*
*/
void ACoreCameraControl::OnMoveForward(float deltaTime)
{
	// BP �� GetWorldRotation �� GetComponentRotation �Դϴ�.
	FRotator lsolateYaw = this->GetIsolateYaw(this->m_pCamera->GetComponentRotation());

	// ���� �����̼ǿ� ���� ������ ���͸� ���Ѵ�.
	FVector forward = FRotationMatrix(lsolateYaw).GetScaledAxis(EAxis::X);
	//
	float amount = this->m_fLocateSpeed * deltaTime;

	FVector locate = this->GetAddVec3ToLocate(forward, amount);
	//
	// FString str = FString::Printf(TEXT("locate X : %d, Y : %d, X : %d"), locate.X, locate.Y, locate.Z);
	// GEngine->AddOnScreenDebugMessage(10, 5.f, FColor::Red, str);

	this->SetActorLocation(locate);
}

/*
*/
void ACoreCameraControl::OnMoveRight(float deltaTime)
{
	// BP �� GetWorldRotation �� GetComponentRotation �Դϴ�.
	FRotator lsolateYaw = this->GetIsolateYaw(this->m_pCamera->GetComponentRotation());

	// ���� �����̼ǿ� ���� ����Ʈ ���͸� ���Ѵ�.
	FVector right = FRotationMatrix(lsolateYaw).GetScaledAxis(EAxis::Y);
	//
	float amount = this->m_fLocateSpeed * deltaTime;

	FVector locate = this->GetAddVec3ToLocate(right, amount);
	//
	this->SetActorLocation(locate);
}

/*
*/
void ACoreCameraControl::OnRotatePitch(float delta) 
{
	if (this->m_bRotateCam)
	{
		this->m_fCamYaw = (this->m_fRotateSpeed * delta) + this->m_fCamYaw;
		this->OnUpdateLocateAndRotate();
	}
	else
	{
		// �̵�
		float x, y, normalize = 0.f;
		int32 sizeX, sizeY = 0;
		//
		bool check = this->m_pController->GetMousePosition(x, y);
		//
		if (!check) return;
		//
		this->m_pController->GetViewportSize(sizeX, sizeY);

		normalize = y / sizeY;
		if (normalize < 0.03f)
		{
			this->OnMoveForward(1.f);
		}
		else if (normalize > 0.97f)
		{
			this->OnMoveForward(-1.f);
		}
	}
}

/*

*/
void ACoreCameraControl::OnRotateYaw(float delta)
{
	if (this->m_bRotateCam)
	{
		float update = (this->m_fRotateSpeed * delta) + this->m_fCamPitch;
		this->m_fCamPitch = FMath::Clamp<float>(update, 10.f, 70.f);
		this->OnUpdateLocateAndRotate();
	}
	else
	{
		// �̵�
		float x, y, normalize = 0.f;
		int32 sizeX, sizeY = 0;
		//
		bool check = this->m_pController->GetMousePosition(x, y);
		//
		if (!check) return;
		//
		this->m_pController->GetViewportSize(sizeX, sizeY);

		normalize = x / sizeX;
		if (normalize < 0.1f)
		{
			this->OnMoveRight(-1.f);
		}
		else if (normalize > 0.9f)
		{
			this->OnMoveRight(1.f);
		}
	}
}

/*

*/
void ACoreCameraControl::OnZoomIn()
{
	this->m_fCamDist = FMath::Clamp<float>(m_fCamDist - m_fZoomSpeed, m_fCamDistMin, m_fCamDistMax);
	this->OnUpdateLocateAndRotate();
}

/*

*/
void ACoreCameraControl::OnZoomOut()
{
	this->m_fCamDist = FMath::Clamp<float>(m_fCamDist + m_fZoomSpeed, m_fCamDistMin, m_fCamDistMax);
	this->OnUpdateLocateAndRotate();
}
#pragma endregion



