// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoneycombActor.generated.h"

class UCurveFloat;
class UBoxComponent;
UCLASS()
class CANDY_API AHoneycombActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHoneycombActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateBoxDownAnimation(float DeltaTime);
	UFUNCTION()
	void UpdateBoxUpAnimation(float DeltaTime);
	
	UFUNCTION()
	void OnComponentBeginOverlapEvent
	(UPrimitiveComponent* OverlappedComponent,
	 AActor* OtherActor, UPrimitiveComponent* OtherComp,
	 int32 OtherBodyIndex, bool bFromSweep,
	 const FHitResult& SweepResult);
	
protected:
	
	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveAnimation;

	float AnimationCurveTime0;
	float AnimationCurveTime1;
	UPROPERTY(EditAnywhere)
	float DestroyTime;
	UPROPERTY(EditAnywhere)
	int32 LiftMM;

	bool PlayAnim;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxColl0;
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxColl1;
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxColl2;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent*StaticMesh;

	UPROPERTY(EditAnywhere)
	UMaterialInterface*MaterialInterface;
};
