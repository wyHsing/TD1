// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBasicAIController.h"
#include "WayPoint.h"

void AEnemyBasicAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (Result.IsSuccess()) {
		//go to next
		if (CurWayPoint->NextWayPoint) {
			CurWayPoint = CurWayPoint->NextWayPoint;
			MoveToActor(CurWayPoint, 5.0f);
			UE_LOG(LogTemp, Warning, TEXT("TD1: AI Movement Go to next."));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("TD1: AI Movement Finished."));
		}
	}
	else if(Result.IsInterrupted()){
		UE_LOG(LogTemp, Warning, TEXT("TD1: AI Movement Interrupted"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TD1: AI Movement Failed"));
	}
}

void AEnemyBasicAIController::MoveToWayPoint(AWayPoint* TargetWayPoint)
{
	APawn* controlledPawn = GetPawn();
	if (controlledPawn) {
		// get start way point from game state;
		if (TargetWayPoint) {
			CurWayPoint = TargetWayPoint;
			MoveToActor(CurWayPoint, 5.0f);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TD1: controlledPawn get failed."));
	}
}
