// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyBase.generated.h"

class UFloatingPawnMovement;
UCLASS()
class TD1_API AEnemyBase : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TD1: Movement")
	UFloatingPawnMovement* MovementComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
