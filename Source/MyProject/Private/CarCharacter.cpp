// Fill out your copyright notice in the Description page of Project Settings.


#include "CarCharacter.h"

// Sets default values
ACarCharacter::ACarCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	TObjectPtr<USceneComponent> Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshResource(TEXT("/Script/Engine.StaticMesh'/Game/CarObj.CarObj'"));
	TObjectPtr<UStaticMesh> StaticMesh = StaticMeshResource.Object;
	StaticMeshComponent->SetStaticMesh(StaticMesh);


	FVector Scale = GetActorScale();
	Scale = Scale * 20;
	SetActorScale3D(Scale);

	FRotator Rotation = GetActorRotation();
	Rotation.Roll += 90;
	SetActorRotation(Rotation);



	Acceleration = 50.f;
	OnAir = false;
	MaxSpeed = 1000.f;
	MinSpeed = 200.f;
	BaseSpeed = 400.f;
	BaseTurnRate = 45.f;

	
}

// Called when the game starts or when spawned
void ACarCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACarCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	BaseSpeed += Acceleration * DeltaTime;
	if (BaseSpeed < MinSpeed) {
		BaseSpeed = MinSpeed;
	}
	if (BaseSpeed > MaxSpeed) {
		BaseSpeed = MaxSpeed;
	}
	FVector Location = GetActorLocation();
	Location.Y += BaseSpeed * DeltaTime;
	SetActorLocation(Location);

}

// Called to bind functionality to input
void ACarCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



	PlayerInputComponent->BindAxis("MoveForward", this, &ACarCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &ACarCharacter::Turn);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACarCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACarCharacter::StopJumping);
}


void ACarCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		BaseSpeed += Value * 2 * Acceleration * GetWorld()->GetDeltaSeconds();
	}
}

void ACarCharacter::Turn(float Value)
{
	FRotator Rotation = GetActorRotation();
	Rotation.Yaw += Value * BaseTurnRate;
	SetActorRotation(Rotation);
}

