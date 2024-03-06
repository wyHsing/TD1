// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyBasicAIController.generated.h"

/**
 * 
 */
class AWayPoint;
UCLASS()
class TD1_API AEnemyBasicAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void MoveToWayPoint(AWayPoint* TargetWayPoint);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TD1|WayPoint")
	AWayPoint* CurWayPoint = nullptr;

	
};
