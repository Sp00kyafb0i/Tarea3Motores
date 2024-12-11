// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeshObjectSpawner.generated.h"

UCLASS()
class SPAWNERPLUGIN_API AMeshObjectSpawner : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMeshObjectSpawner();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Mesh actor to use for spawning (must be present in the scene)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    AActor* TargetMeshActor;

    // Object to spawn
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    TSubclassOf<AActor> ObjectToSpawn;

    // Number of objects to spawn
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
    int32 NumberOfObjects;

    // Spawns objects on the mesh
    UFUNCTION(BlueprintCallable, Category = "Spawner")
    void SpawnObjects();

private:
    FVector GetRandomPointOnMesh();
};
