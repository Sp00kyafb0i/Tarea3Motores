// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


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
	Speed = 0.f;
	OnAir = false;

}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Speed += Acceleration * DeltaTime;
	FVector Location = GetActorLocation();
	Location.Y += Speed * DeltaTime;
	SetActorLocation(Location);
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

