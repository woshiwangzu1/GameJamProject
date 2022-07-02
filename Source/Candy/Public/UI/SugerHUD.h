// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SugerHUD.generated.h"

/**
 * 
 */
class ULoginUserWidget;
class URoomListUserWidget;
class UMainWidget;

UCLASS()
class CANDY_API ASugerHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void ShowLogin();
	
	UFUNCTION(BlueprintCallable)
	void ShowRoomListUI();
	


protected:
	UPROPERTY(BlueprintReadOnly)
	ULoginUserWidget* LoginUserWidget;
	UPROPERTY(BlueprintReadOnly)
	UMainWidget* MainWidget;
	UPROPERTY(BlueprintReadOnly)
	URoomListUserWidget* RoomListUserWidget;
	
};
