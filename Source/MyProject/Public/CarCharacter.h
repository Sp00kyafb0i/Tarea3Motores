// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CarCharacter.generated.h"


UCLASS()
class MYPROJECT_API ACarCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACarCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void MoveForward(float Value);
	void Turn(float Value);



	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	float Acceleration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	float BaseSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	float MaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	float MinSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	bool OnAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	float BaseTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	float SideSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	float MinYaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	float MaxYaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	float isTurning;
};
