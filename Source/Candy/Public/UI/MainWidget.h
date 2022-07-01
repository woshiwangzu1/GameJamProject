// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */

class UButton;
UCLASS()
class CANDY_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void LoginButton();


protected:
	UPROPERTY(meta=(BindWidget))
	UButton* Login;
};
