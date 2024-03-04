// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TD1GameStateBase.generated.h"

/**
 * 
 */
class AWayPoint;
UCLASS()
class TD1_API ATD1GameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TD1_WayPoint")
	AWayPoint* StartWayPoint = nullptr;
};
