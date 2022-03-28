// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtleActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

//DEFINE_LOG_CATEGORY_STATIC(LogActor, All, All)

// Sets default values
ATurtleActor::ATurtleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurtleMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurtleMesh");
	SetRootComponent(TurtleMesh);
}

// Called when the game starts or when spawned
void ATurtleActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	FVector::DistSquared(InitialLocation, Destination);
	PathVector = Destination - InitialLocation;
	PathVector.Normalize();

	switch (MoveType)
	{
		case EMovementType::Straight: break;
		case EMovementType::Stopped:
		{
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtleActor::OnTimerFiredStop, TimerRate, true);
			break;
		}
		case EMovementType::Reversed:
		{
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtleActor::OnTimerFiredReverse, TimerRate, true);
			break;
		}
		default:break;
	}	
}

// Called every frame
void ATurtleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
}

void ATurtleActor::HandleMovement()
{

	FVector CurrentLocation = GetActorLocation();
	float DeltaT = LocalSpeed * Delta;
	if (GetWorld())
	{
		CurrentLocation += PathVector * DeltaT;
		SetActorLocation(CurrentLocation);
		if (CurrentLocation.Equals(Destination, 10.0f)) {
			Super::Destroy();
		}
	} 

}

void ATurtleActor::OnTimerFiredStop()
{
	LocalSpeed = 0.0f;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtleActor::OnTimerFiredStraight, TimerRate / 2, true);
}

void ATurtleActor::OnTimerFiredStraight() {
	LocalSpeed = Speed;
	if (MoveType == EMovementType::Stopped) {
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtleActor::OnTimerFiredStop, TimerRate, true);
	}
	else {
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtleActor::OnTimerFiredReverse, TimerRate, true);
	}
}

void ATurtleActor::OnTimerFiredReverse() {

	LocalSpeed = -Speed;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtleActor::OnTimerFiredStraight, TimerRate / 2, true);
}


