// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneProps/HoneycombActor.h"

#include "Candy/CandyCharacter.h"
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
	BoxColl0->SetBoxExtent(FVector(100,100,5));
	BoxColl1->SetBoxExtent(FVector(99,99,4));
	BoxColl2->SetBoxExtent(FVector(98,98,3));
	bReplicates=true;
	PlayAnim=false;
	AnimationCurveTime0=0.f;
	AnimationCurveTime1=0.f;
	DestroyTime=0.3f;
	LiftMM=15;
}

// Called when the game starts or when spawned
void AHoneycombActor::BeginPlay()
{
	Super::BeginPlay();
	BoxColl0->OnComponentBeginOverlap.AddDynamic(this,&AHoneycombActor::OnComponentBeginOverlapEvent);
	BoxColl1->OnComponentBeginOverlap.AddDynamic(this,&AHoneycombActor::OnComponentBeginOverlapEvent);
	BoxColl2->OnComponentBeginOverlap.AddDynamic(this,&AHoneycombActor::OnComponentBeginOverlapEvent);
}

// Called every frame
void AHoneycombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayAnim)
	{
		UpdateBoxDownAnimation(DeltaTime);
	}
}

void AHoneycombActor::UpdateBoxDownAnimation(float DeltaTime)
{
	if(!CurveAnimation) return;
	float CurveValue=CurveAnimation->GetFloatValue(AnimationCurveTime0);
	float MinTime=0.f;
	float MaxTime=0.f;
	CurveAnimation->GetTimeRange(MinTime,MaxTime);
	if(StaticMesh) StaticMesh->SetRelativeLocation(FVector(0,0,FMath::Lerp(0,-LiftMM,CurveValue)));	
	AnimationCurveTime0+=DeltaTime;
	if(AnimationCurveTime0>=MaxTime)
	{
		UpdateBoxUpAnimation(DeltaTime);
		StaticMesh->SetMaterial(0,MaterialInterface);
	}
}

void AHoneycombActor::UpdateBoxUpAnimation(float DeltaTime)
{
	if(!CurveAnimation) return;
	float CurveValue=CurveAnimation->GetFloatValue(AnimationCurveTime1);
	float MinTime=0.f;
	float MaxTime=0.f;
	CurveAnimation->GetTimeRange(MinTime,MaxTime);
	if(StaticMesh) StaticMesh->SetRelativeLocation(FVector(0,0,FMath::Lerp(-LiftMM,0,CurveValue)));	
	AnimationCurveTime1+=DeltaTime;
	if(AnimationCurveTime1>=(MaxTime+DestroyTime))
	{
		Destroy();	
	}
}

void AHoneycombActor::OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACandyCharacter*CandyCharacter=Cast<ACandyCharacter>(OtherActor))
	{
		PlayAnim=true;
	}	
}
