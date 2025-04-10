// Fill out your copyright notice in the Description page of Project Settings.


#include "CarCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ACarCharacter::ACarCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//TObjectPtr<USceneComponent> Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(GetCapsuleComponent());
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(GetCapsuleComponent());

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshResource(TEXT("/Script/Engine.StaticMesh'/Game/CarObj.CarObj'"));
	TObjectPtr<UStaticMesh> StaticMesh = StaticMeshResource.Object;
	StaticMeshComponent->SetStaticMesh(StaticMesh);
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->SetRelativeScale3D(FVector(20.f, 20.f, 20.f));
	
	
	

	//FVector Scale = GetActorScale();
	//Scale = Scale * 20;
	//SetActorScale3D(Scale);

	FRotator Rotation = GetActorRotation();
	Rotation.Roll += 90;
	//Rotation.Yaw -= 90;
	SetActorRotation(Rotation);



	Acceleration = 500.f;
	OnAir = false;
	MaxSpeed = 2000.f;
	MinSpeed = 200.f;
	BaseSpeed = 400.f;
	BaseTurnRate = 45.f;
	SideSpeed = 200.f;
	MinYaw = -60.f;
	MaxYaw = 60.f;
	isTurning = false;


}

// Called when the game starts or when spawned
void ACarCharacter::BeginPlay()
{
	Super::BeginPlay();

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->GravityScale = 1.0f;
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	

}

// Called every frame
void ACarCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (Controller)
	{
		//AddMovementInput(GetActorForwardVector(), BaseSpeed * DeltaTime);
	}

	// Smoothly return to center if not turning
	if (!isTurning)
	{
		FRotator CurrentRotation = GetActorRotation();
		CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, 0.0f, DeltaTime, BaseTurnRate / 10);
		SetActorRotation(CurrentRotation);
	}

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
		BaseSpeed = FMath::Clamp(BaseSpeed + Value * Acceleration, MinSpeed, MaxSpeed);
	}
}

void ACarCharacter::Turn(float Value)
{


	if (Controller && Value != 0.0f)
	{
		FVector Location = GetActorLocation();
		Location.X -= SideSpeed * Value * GetWorld()->GetDeltaSeconds();
		SetActorLocation(Location);

		FRotator Rotation = GetActorRotation();
		Rotation.Yaw = FMath::ClampAngle(Rotation.Yaw + BaseTurnRate * GetWorld()->GetDeltaSeconds() * Value, MinYaw, MaxYaw);
		SetActorRotation(Rotation);

		isTurning = true;
		
	}
	else
	{
		isTurning = false;
	}
}
