// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUserWidget.generated.h"

/**
 * 
 */

class UEditableTextBox;

UCLASS()
class CANDY_API ULoginUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;


protected:

	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* Name;

public:
	UPROPERTY(BlueprintReadOnly)
	FText NameText;
};
