// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneProps/DestroyFloor.h"
#include "Candy/CandyCharacter.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ADestroyFloor::ADestroyFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentLocation=FVector2D(0,0);
	NextLocation=FVector2D(0,0);
	bCorrect=true;
	bChanged=false;
	ReadyTime=5.0f;
	Time=0.f;
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
void ADestroyFloor::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ADestroyFloor::OnComponentBeginOverlap);
	// while (CurrentLocation.Y!=9)
	// {
	// 	CorrectPath.Add(CurrentLocation);
	// 	int XOffset=CurrentLocation.X==0?FMath::RandRange(0,1):FMath::RandRange(-1,1);
	// 	
	// 	if(XOffset==0)
	// 	{
	// 		UE_LOG(LogTemp, Log, TEXT("1111111111"));
	// 		NextLocation=FVector2D(CurrentLocation.X,CurrentLocation.Y+1);
	// 	 
	// 		UE_LOG(LogTemp, Log, TEXT("next==%d==%d"), NextLocation.X,NextLocation.Y);
	// 	}
	// 	else
	// 	{
	// 		UE_LOG(LogTemp, Log, TEXT("22222222222"));
	// 		NextLocation=FVector2D(CurrentLocation.X,CurrentLocation.Y);
	// 		 
	// 		UE_LOG(LogTemp, Log, TEXT("next==%d==%d"), NextLocation.X,NextLocation.Y);
	// 	}
	// 	NextLocation=FVector2D(CurrentLocation.X+XOffset,NextLocation.Y);
	//  
	// 	UE_LOG(LogTemp, Log, TEXT("next==%d==%d"), NextLocation.X,NextLocation.Y);
	// 	if(CorrectPath.Contains(NextLocation))
	// 	{
	// 		continue;
	// 	}
	// 	CurrentLocation=NextLocation;
	// 	
	// 	UE_LOG(LogTemp, Log, TEXT("current==%d==%d"), CurrentLocation.X,CurrentLocation.Y);
	// }
}

void ADestroyFloor::OnComponentBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweppResult)
{
	UE_LOG(LogTemp, Log, TEXT("====碰撞"));
	if(ACandyCharacter*Player=Cast<ACandyCharacter>(OtherActor))
	{
		 if(!bCorrect)
		 {
		 	FTimerHandle Handle;
		 	GetWorld()->GetTimerManager().SetTimer(Handle,this,&ADestroyFloor::DestroyFloor,0.1f);
		 }
	}
}

// void ADestroyFloor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
// 	DOREPLIFETIME(ADestroyFloor, bCorrect);
// }

// void ADestroyFloor::Server_ChangeColor_Implementation(bool bCorrect)
// {
// }
//
// bool ADestroyFloor::Server_ChangeColor_Validate(bool bCorrect)
// {
// }


// Called every frame
void ADestroyFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Time+=DeltaTime;
if(bCorrect&&Time<=ReadyTime&&!bChanged)
{
	Appear();
}
}

void ADestroyFloor::Appear()
{
	// if (!HasAuthority())
	// {
	// 	Server_ChangeColor_Validate();
	// }
	PlaneComp->SetMaterial(0,MaterialInterface1);
	bChanged=true;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle,this,&ADestroyFloor::ReSet,5.f);
}
void ADestroyFloor::SetIndex(FVector2D Index)
{
	FloorIndex=Index;
}

void ADestroyFloor::DestroyFloor()
{
	Destroy();
}

void ADestroyFloor::ReSet()
{
	PlaneComp->SetMaterial(0,MaterialInterface2);
}

