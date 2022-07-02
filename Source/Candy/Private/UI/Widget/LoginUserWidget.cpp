// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/LoginUserWidget.h"

#include "Components/EditableTextBox.h"

void ULoginUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	NameText = Name->GetText();
}
