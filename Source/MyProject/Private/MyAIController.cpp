// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Actor.h"

void AMyAIController::BeginPlay()
{
    Super::BeginPlay();

    // Initialize the Behavior Tree if available
    if (BehaviorTree)
    {
        // Run the Behavior Tree
        RunBehaviorTree(BehaviorTree);

        // Initialize the Blackboard
        BlackboardComp = GetBlackboardComponent();
    }
}

void AMyAIController::MoveToTarget(const FVector& TargetLocation)
{
    if (BlackboardComp)
    {
        // Set the TargetLocation key in the Blackboard
        BlackboardComp->SetValueAsVector("TargetLocation", TargetLocation);
    }
}


void AMyAIController::SetTargetActor(AActor* TargetActor)
{
    if (BlackboardComp)
    {
        // Set the TargetActor key in the Blackboard
        BlackboardComp->SetValueAsObject("TargetActor", TargetActor);
    }
}

void AMyAIController::SetTargetLocation(const FVector& Location)
{
    if (BlackboardComp) // Asegúrate de que el Blackboard está inicializado
    {
        // Actualiza la clave TargetLocation en el Blackboard
        BlackboardComp->SetValueAsVector("TargetLocation", Location);
    }
}