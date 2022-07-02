// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Seesaw.generated.h"
class ACandyCharacter;
UCLASS()
class CANDY_API ASeesaw : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASeesaw();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor,
								 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,

								 const FHitResult& SweppResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent*PlaneComp;
	UPROPERTY(EditAnywhere)
	UStaticMesh*Plane;
	UPROPERTY(EditAnywhere)
	UBoxComponent*BoxComponent;

	
	UPROPERTY(EditAnywhere)
	int32 RotatSpeed;
	TArray<ACandyCharacter*>Players;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SeesawRotat();
};
