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
	RotatingMovement->RotationRate.Yaw=0;
	NewType=EPropType::EPT_NONE;
	NewState=EPropRotateState::EPR_NONE;
}

// Called when the game starts or when spawned
void ARotateActor::BeginPlay()
{
	Super::BeginPlay();
	ChangePropRotateState(NewState);
}

void ARotateActor::ChangePropRotateType(EPropType Type)
{
	
}

void ARotateActor::ChangePropRotateState(EPropRotateState State)
{
	NewState=State;
	switch (NewState)
	{
	case EPropRotateState::EPR_NONE:
		Speed=0;
		Direction=0;
		break;
	case EPropRotateState::EPR_Roll:
		RotatingMovement->RotationRate.Roll=Speed*Direction;
		break;
	case EPropRotateState::EPR_Pitch:
		RotatingMovement->RotationRate.Pitch=Speed*Direction;
		break;
	case EPropRotateState::EPR_Yaw:
		RotatingMovement->RotationRate.Yaw=Speed*Direction;
		break;
	default:
		Speed=0;
		Direction=0;
		
		break;
			
	}
}


// Called every frame
void ARotateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

