// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnButton.h"
#include "TurtleActor.h"
#include "Engine/Engine.h"

// Sets default values
ASpawnButton::ASpawnButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnButton::DoSpawn(const float& Speed, const EMovementType& Type, const FVector& SpawnLocation) {
	UWorld* World = GetWorld();
	if (World) {
		const FTransform Transform = FTransform(FRotator::ZeroRotator, SpawnLocation);
		ATurtleActor* Turtle = World->SpawnActor<ATurtleActor>(TurtleClass, Transform);
		if (Turtle) {
			UE_LOG(LogTemp, Display, TEXT("Spawning: Speed = %f"), Speed);
			Turtle->SetSpeed(Speed);
			Turtle->SetMoveType(Type);
			Turtle->FinishSpawning(Transform);
		}
	}
}