// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemyBase;
UCLASS()
class TD1_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// Regular Spawning function
	UFUNCTION(BlueprintCallable, Category = "TD1|EnemySpawner")
	void StartSpawning(int32 number, float time, FVector location = FVector::ZeroVector, FRotator rotation = FRotator::ZeroRotator, bool isLoop = false);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Init
	void Initialize();

	//Spawn Enemies
	void Spawn(FVector location, FRotator rotation);	
	//Object Pool - ReuseOrCreate
	AEnemyBase* GetObject();
	//Object Pool - Return
	//TODO: Subscribe? Listener?
	void ReturnObject(AEnemyBase* returnedObject);
	//List
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TD1|EnemySpawner")
	TSubclassOf<AEnemyBase> chosenEnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TD1|EnemySpawner")
	int32 initialPoolSize = 5;
	// "x" sec per on object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TD1|EnemySpawner")
	float spawnTime = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TD1|EnemySpawner")
	float firstDelayTime = 1.0f;
	// total number of enemy you want to spawn in certain level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TD1|EnemySpawner")
	int32 totalDesiredSpawnNumber = 2;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TD1|EnemySpawner")
	TArray<AEnemyBase*> objectPool;

	// "x" number waiting for spawning
	int32 remainSpawnNumber = -1;
	//Timer Handle for spawning
	FTimerHandle spawnTimerHandle;
private:



};
