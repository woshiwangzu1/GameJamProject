// Fill out your copyright notice in the Description page of Project Settings.


// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneProps/Seesaw.h"

#include <ThirdParty/openexr/Deploy/OpenEXR-2.3.0/OpenEXR/include/ImathFun.h>

#include "Candy/CandyCharacter.h"

// Sets default values
ASeesaw::ASeesaw()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
 
	RotatSpeed=5000;
	RootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	PlaneComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneComp"));
	PlaneComp->SetupAttachment(RootComponent);
	Plane=ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'")).Object;
	PlaneComp->SetStaticMesh(Plane);
	BoxComponent=CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComponent->SetupAttachment(PlaneComp);
	BoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	
}

// Called when the game starts or when spawned
void ASeesaw::BeginPlay()
{
	Super::BeginPlay();
	 
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ASeesaw::OnComponentBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this,&ASeesaw::OnComponentEndOverlap);
	PlaneComp->SetMaterial(0,MaterialInterface1);
}

void ASeesaw::OnComponentBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweppResult)
{
	UE_LOG(LogTemp, Log, TEXT("====有人上了板子"));
	if(ACandyCharacter*Player=Cast<ACandyCharacter>(OtherActor))
	{
		if(!Players.Contains(Player))
		{
			Players.Add(Player);
		}
		
	}
}

void ASeesaw::OnComponentEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("====有人下了板子"));
	if(ACandyCharacter*Player=Cast<ACandyCharacter>(OtherActor))
	{
		 Players.Remove(Player);
	}
}


// Called every frame
void ASeesaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Players.Num()>0)
{
	SeesawRotat();
}
else
	{
	Reset();
	}
}

void ASeesaw::SeesawRotat()
{
	for(auto P:Players)
	{
		float Distance=GetActorLocation().X-P->GetActorLocation().X;
		 
			AddActorWorldRotation(FRotator(Distance/RotatSpeed,0,0));
			
			P->AddActorWorldOffset(FVector(GetActorRotation().Pitch*(-0.03),0,0));
		 
	}
}

