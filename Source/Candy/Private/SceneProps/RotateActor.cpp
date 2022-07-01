// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneProps/RotateActor.h"

#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
ARotateActor::ARotateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RotatingMovement=CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComp"));
	Speed=40;
	Direction=1;
}

// Called when the game starts or when spawned
void ARotateActor::BeginPlay()
{
	Super::BeginPlay();
	RotatingMovement->RotationRate.Yaw=Speed*Direction;
}

// Called every frame
void ARotateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

