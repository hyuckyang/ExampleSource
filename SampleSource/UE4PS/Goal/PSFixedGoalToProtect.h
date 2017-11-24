// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameMode/PSFieldGameMode.h"
#include "PSFixedGoalToProtect.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(GoalUpdateDelegate, int32, int32);
/**
 *
 */
UCLASS()
class UE4PS_API APSFixedGoalToProtect : public AActor
{
	GENERATED_BODY()
	
	GoalUpdateDelegate m_goalUpdateDelegate;
public:	

	APSFixedGoalToProtect();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnInColliderBeginOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
								  int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweeppResult);

	UFUNCTION()
	void OnInColliderEndOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
								int32 otherBodyIndex);

	template<typename T>
	void GoalUpdateFuncBind(UObject* obj, void (T::*funcPoint)(int32, int32)) { m_goalUpdateDelegate.AddUObject(Cast<T>(obj), funcPoint); }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent*			m_BoxComp;

	int32					m_GoalTotalHP = 10;
	int32					m_GoalHP = 10;
};
