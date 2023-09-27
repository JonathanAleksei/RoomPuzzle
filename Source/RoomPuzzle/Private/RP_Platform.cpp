// Fill out your copyright notice in the Description page of Project Settings.


#include "RP_Platform.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARP_Platform::ARP_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRoot")); 
	RootComponent = CustomRootComponent;

	PlatformMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMeshComponent->SetupAttachment(CustomRootComponent);

	bIsGoigUp=true;
	MinHeight=0.0f;
	MaxHeight=50.0f;
	Speed=10.0f;
	
	
}

// Called when the game starts or when spawned
void ARP_Platform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARP_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ARP_Platform::Move()
{
	FVector upDirection = UKismetMathLibrary::GetUpVector(GetActorRotation());

	if (bIsGoigUp)
	{
		upDirection = upDirection*1;
	}
	else
	{
		upDirection = upDirection*-1;
	}

	FVector CurrentVelocity =  upDirection * Speed;
	FVector NewPosition = GetActorLocation() + CurrentVelocity;
	SetActorLocation(NewPosition);

	if (bIsGoigUp && GetActorLocation().Z >= MaxHeight || !bIsGoigUp && GetActorLocation().Z <= MinHeight)
	{
		bIsGoigUp = !bIsGoigUp;
	}
}

