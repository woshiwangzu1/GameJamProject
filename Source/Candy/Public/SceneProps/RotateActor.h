// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateActor.generated.h"

UENUM()
enum class EPropType:uint8
{
	EPT_NONE,
};

class URotatingMovementComponent;

UCLASS()
class CANDY_API ARotateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotateActor();

	
protected:
	UPROPERTY(EditAnywhere)
	int32 Direction;
	UPROPERTY(EditAnywhere)
	int32 Speed;
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	URotatingMovementComponent*RotatingMovement;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
