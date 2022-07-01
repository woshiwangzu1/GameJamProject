// Fill out your copyright notice in the Description page of Project Settings.


#include "Candy/Public/Scene/SceneItemActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASceneItemActor::ASceneItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASceneItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASceneItemActor::CallBack(int32 Num)
{
}

// Called every frame
void ASceneItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateSceneFunc(DeltaTime);


	if (APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0)))
	{
		if (PC->WasInputKeyJustPressed(EKeys::E))
		{
			if (GMDel.IsBound())
			{
				GMDel.Execute(1);
			}
			if (GMDelegateTwo.IsBound())
			{
				int32 Num = GMDelegateTwo.Execute(1);
			}
			if (MultiDelegateTest.IsBound())
			{
				MultiDelegateTest.Broadcast(123);
				FDelegateHandle Handle = MultiDelegateTest.AddUObject(this,&ASceneItemActor::CallBack);
				MultiDelegateTest.Remove(Handle);
			}
		}
		
	}
	
}

