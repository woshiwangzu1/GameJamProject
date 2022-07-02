// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneProps/FruitLevel.h"



// Sets default values
AFruitLevel::AFruitLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFruitLevel::BeginPlay()
{
	Super::BeginPlay();
	// FVector fv;
	// FVector OffectX(210,0,0);
	// FVector OffectY(0,210,0);
	// for (int32 i=0;i<15;i++)
	// {
	// 	fv=i/4*OffectX+i%4*OffectY;
	// 	
	// 	AFruitsBlock* Fruit = GetWorld()->SpawnActor<AFruitsBlock>(AFruitsBlock::StaticClass(),fv,FRotator::ZeroRotator);
	// 	//Block.Add(Fruit);
	// }
}

// Called every frame
void AFruitLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

