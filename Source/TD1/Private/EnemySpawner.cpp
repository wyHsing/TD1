// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "EnemyBase.h"
// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

void AEnemySpawner::StartSpawning(int32 number, float time, FVector location, FRotator rotation, bool isLoop)
{
	totalDesiredSpawnNumber = number;
	spawnTime = time;
	remainSpawnNumber = totalDesiredSpawnNumber;

	if (GetWorldTimerManager().IsTimerActive(spawnTimerHandle)) {
		GetWorldTimerManager().ClearTimer(spawnTimerHandle);
	}
	GetWorldTimerManager().SetTimer(spawnTimerHandle, [this, location, rotation, isLoop]() {

		Spawn(location, rotation);
		remainSpawnNumber--;
		if (remainSpawnNumber == 0) {
			if (isLoop) {
				remainSpawnNumber = totalDesiredSpawnNumber;
			}
			else {
				GetWorldTimerManager().ClearTimer(spawnTimerHandle);
			}
		}
	}, spawnTime, true, firstDelayTime);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

void AEnemySpawner::Initialize()
{
	for (int32 i = 0; i < initialPoolSize; ++i) {
		AEnemyBase* newActor = GetWorld()->SpawnActor<AEnemyBase>(chosenEnemyClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (newActor) {
			newActor->SetActorHiddenInGame(true);
			objectPool.Add(newActor);
		}
	}
}

void AEnemySpawner::Spawn(FVector location, FRotator rotation)
{
	//TODO: enemy initialize?
	AEnemyBase* spawningObject = GetObject();
	if (spawningObject) {
		spawningObject->SetActorLocation(location);
		spawningObject->SetActorRotation(rotation);
		spawningObject->Initialize();
	}
	return;
}

AEnemyBase* AEnemySpawner::GetObject()
{
	for (AEnemyBase* object : objectPool) {
		if (!object->IsActorBeingDestroyed() && object->IsHidden()) {
			object->SetActorHiddenInGame(false);
			return object;
		}
	}
	// otherwise create one
	AEnemyBase* newActor = GetWorld()->SpawnActor<AEnemyBase>(chosenEnemyClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if (newActor) {
		newActor->SetActorHiddenInGame(false);
		objectPool.Add(newActor);
		return newActor;
	}

	return nullptr;
}

void AEnemySpawner::ReturnObject(AEnemyBase* returnedObject)
{
	//TODO: call by delegate?
	if (returnedObject) {
		returnedObject->SetActorHiddenInGame(true);
	}
}


