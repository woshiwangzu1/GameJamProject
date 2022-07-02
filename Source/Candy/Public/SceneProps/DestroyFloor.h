// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyFloor.generated.h"
class UBoxComponent;
UCLASS()
class CANDY_API ADestroyFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyFloor();
protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent*PlaneComp;
	UPROPERTY(EditAnywhere)
	UStaticMesh*Plane;
	UPROPERTY(EditAnywhere)
	UBoxComponent*BoxComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor,
									 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
									 const FHitResult& SweppResult);
FVector2D CurrentLocation;
FVector2D NextLocation;
	UPROPERTY(BlueprintReadOnly)
FVector2D FloorIndex;
	UPROPERTY(BlueprintReadWrite)
	bool bCorrect;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
void SetIndex(FVector2D Index);
	void DestroyFloor();
	TArray<FVector2D>CorrectPath;
};
