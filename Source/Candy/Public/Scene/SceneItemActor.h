// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneItemActor.generated.h"
DECLARE_DELEGATE_OneParam(GMDelegateOne,int32)
DECLARE_DELEGATE_RetVal_OneParam(int32,GMDelegateTwo,int32)
DECLARE_MULTICAST_DELEGATE_OneParam(MultiDelegateTest,int32)

DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateTest,int32,Number);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateTestMulti,int32,Number);
UCLASS()
class CANDY_API ASceneItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSceneFunc(float DeltaTime);
	void CallBack(int32 Num);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	GMDelegateOne GMDel;
	GMDelegateTwo GMDelegateTwo;
	MultiDelegateTest MultiDelegateTest;
};
