// Fill out your copyright notice in the Description page of Project Settings.


// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneProps/Seesaw.h"

#include "Candy/CandyCharacter.h"

// Sets default values
ASeesaw::ASeesaw()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
ScaleX=10.0f;
ScaleY=2.0f;
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
	ScaleX=FMath::RandRange(6,15);
	ScaleY=FMath::RandRange(0.8,2);
	PlaneComp->SetWorldScale3D(FVector(ScaleX,ScaleY,0.3));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ASeesaw::OnComponentBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this,&ASeesaw::OnComponentEndOverlap);
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
}

void ASeesaw::SeesawRotat()
{
	for(auto P:Players)
	{
		float Distance=GetActorLocation().X-P->GetActorLocation().X;
		SetActorRotation(FRotator(0,Distance/RotatSpeed,0));
		P->AddActorWorldOffset(FVector(GetActorRotation().Pitch*(-0.3),0,0));
	}
}

