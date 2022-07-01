// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SugerHUD.generated.h"

/**
 * 
 */
class ULoginUserWidget;
UCLASS()
class CANDY_API ASugerHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void ShowLogin();


protected:
	UPROPERTY()
	ULoginUserWidget* LoginUserWidget;
	
};
