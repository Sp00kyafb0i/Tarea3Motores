#include "MeshObjectSpawner.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AMeshObjectSpawner::AMeshObjectSpawner()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    TargetMeshActor = nullptr;
}

void AMeshObjectSpawner::BeginPlay()
{
    Super::BeginPlay();

    // Spawn objects at the beginning
    SpawnObjects();
}

void AMeshObjectSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMeshObjectSpawner::SpawnObjects()
{
    if (!TargetMeshActor || !ObjectToSpawn || NumberOfObjects <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spawner setup is incomplete."));
        return;
    }

    UStaticMeshComponent* MeshComponent = TargetMeshActor->FindComponentByClass<UStaticMeshComponent>();
    if (!MeshComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Target actor does not have a StaticMeshComponent."));
        return;
    }

    const FBoxSphereBounds Bounds = MeshComponent->Bounds; // Use world bounds

    for (int32 i = 0; i < NumberOfObjects; i++)
    {
        FVector SpawnLocation;
        bool bFoundValidLocation = false;

        // Attempt to find a valid spawn location
        for (int32 Attempts = 0; Attempts < 10; Attempts++) // Try up to 10 times
        {
            // Generate a random point within the world bounds
            SpawnLocation = Bounds.Origin + FVector(
                FMath::FRandRange(-Bounds.BoxExtent.X, Bounds.BoxExtent.X),
                FMath::FRandRange(-Bounds.BoxExtent.Y, Bounds.BoxExtent.Y),
                FMath::FRandRange(-Bounds.BoxExtent.Z, Bounds.BoxExtent.Z)
            );

            // Adjust spawn location to touch the ground
            FHitResult HitResult;
            FVector Start = SpawnLocation + FVector(0, 0, 100); // Start slightly above
            FVector End = SpawnLocation - FVector(0, 0, 1000); // Trace downward

            FCollisionQueryParams QueryParams;
            QueryParams.AddIgnoredActor(this);

            if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
            {
                SpawnLocation = HitResult.Location;
                bFoundValidLocation = true;
                break;
            }
        }

        if (!bFoundValidLocation)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to find a valid spawn location."));
            continue;
        }

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        GetWorld()->SpawnActor<AActor>(ObjectToSpawn, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

        // Optional: Debug point
        DrawDebugSphere(GetWorld(), SpawnLocation, 25.0f, 12, FColor::Green, false, 10.0f);
    }
}

FVector AMeshObjectSpawner::GetRandomPointOnMesh()
{
    if (!TargetMeshActor)
    {
        return FVector::ZeroVector;
    }

    UStaticMeshComponent* MeshComponent = TargetMeshActor->FindComponentByClass<UStaticMeshComponent>();
    if (!MeshComponent || !MeshComponent->GetStaticMesh())
    {
        return FVector::ZeroVector;
    }

    const FBoxSphereBounds Bounds = MeshComponent->Bounds; // Use world bounds

    // Generate random point within the world bounds
    FVector RandomPoint = Bounds.Origin + FVector(
        FMath::FRandRange(-Bounds.BoxExtent.X, Bounds.BoxExtent.X),
        FMath::FRandRange(-Bounds.BoxExtent.Y, Bounds.BoxExtent.Y),
        FMath::FRandRange(-Bounds.BoxExtent.Z, Bounds.BoxExtent.Z)
    );

    return RandomPoint;
}