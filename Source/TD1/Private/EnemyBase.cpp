// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "EnemyBasicAIController.h"
#include "TD1GameStateBase.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	movementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("EnemyBaseMovement"));
	movementComponent->MaxSpeed = 500.f;
}

void AEnemyBase::Initialize()
{
	// create ai controller
	//TODO: best place to do?
	if (myAIController == nullptr) {
		myAIController = GetWorld()->SpawnActor<AEnemyBasicAIController>();
	}
	
	if (myAIController) {
		myAIController->Possess(this);
		ATD1GameStateBase* gameState = Cast<ATD1GameStateBase>(GetWorld()->GetGameState());
		if (gameState) {
			AWayPoint* startWayPoint = gameState->StartWayPoint;
			if (startWayPoint) {
				myAIController->MoveToWayPoint(startWayPoint);
			}
			else UE_LOG(LogTemp, Warning, TEXT("TD1: Start way point is null."));
		}
		else UE_LOG(LogTemp, Warning, TEXT("TD1: GameState get failed."));
	}
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}


