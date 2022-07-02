// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateActor.generated.h"

UENUM(BlueprintType)
enum class EPropType:uint8
{
	EPT_NONE,
	EPT_Cylinder,
	EPT_Disc,
	EPT_Door,
	
};
UENUM(BlueprintType)
enum class EPropRotateState:uint8
{
	EPR_NONE,
	EPR_Yaw,
	EPR_Pitch,
	EPR_Roll,
};
class URotatingMovementComponent;


UCLASS()
class CANDY_API ARotateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotateActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	EPropType NewType;
	
	UPROPERTY(EditAnywhere)
	EPropRotateState NewState;
protected:
	
	UPROPERTY(EditAnywhere)
	int32 Direction;
	
	UPROPERTY(EditAnywhere)
	int32 Speed;

	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent*RotatingMovement;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//判断旋转道具的旋转状态
	UFUNCTION()
	void ChangePropRotateType(EPropType Type);

	//判断旋转道具的旋转状态
	UFUNCTION()
	void ChangePropRotateState(EPropRotateState State);
	
};
