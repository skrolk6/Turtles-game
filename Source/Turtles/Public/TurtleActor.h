// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurtleActor.generated.h"

class UStaticMeshComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Stopped,
	Straight,
	Reversed
};

UCLASS()
class TURTLES_API ATurtleActor : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurtleMesh;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement")
	EMovementType MoveType = EMovementType::Straight;

	UFUNCTION(BluePrintCallable)
	void SetMoveType(const EMovementType& Type) { MoveType = Type; }

	// Sets default values for this actor's properties
	ATurtleActor();

	FOnTimerFinished OnTimerFinished;

	float TimerRate = 1.0f;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement")
	float Speed = 60.0f;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement")
	FVector Destination;

	UFUNCTION(BluePrintCallable)
	void SetSpeed(const float& SpeedVar) { Speed = SpeedVar; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector InitialLocation;
	FVector PathVector;
	float LocalSpeed = Speed;
	float Delta = 0.01f;

	FTimerHandle TimerHandle;

	void HandleMovement();
	void OnTimerFiredStop();
	void OnTimerFiredStraight();
	void OnTimerFiredReverse();

};