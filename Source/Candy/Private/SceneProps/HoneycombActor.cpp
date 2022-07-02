// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneProps/HoneycombActor.h"

#include "Components/BoxComponent.h"

// Sets default values
AHoneycombActor::AHoneycombActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	BoxColl0 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp0"));
	BoxColl0->SetupAttachment(RootComponent);
	BoxColl1 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp1"));
	BoxColl1->SetupAttachment(RootComponent);
	BoxColl2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp2"));
	BoxColl2->SetupAttachment(RootComponent);
	StaticMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	BoxColl0->SetBoxExtent(FVector(150,150,5));
	BoxColl1->SetBoxExtent(FVector(149,149,4));
	BoxColl2->SetBoxExtent(FVector(148,148,3));
}

// Called when the game starts or when spawned
void AHoneycombActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHoneycombActor::UpdateBoxAnimation(float DeltaTime)
{
}

void AHoneycombActor::OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

// Called every frame
void AHoneycombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

