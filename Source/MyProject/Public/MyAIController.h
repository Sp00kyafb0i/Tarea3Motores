// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

// Forward declarations
class UBehaviorTree;
class UBlackboardComponent;

UCLASS()
class MYPROJECT_API AMyAIController : public AAIController
{
    GENERATED_BODY()

protected:
    // Blackboard Component
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    UBlackboardComponent* BlackboardComp;

    // Behavior Tree
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTree;

    virtual void BeginPlay() override;

public:
    // Function to set the target location dynamically
    void MoveToTarget(const FVector& TargetLocation);

    void SetTargetActor(AActor* TargetActor);

    void SetTargetLocation(const FVector& Location);
};

