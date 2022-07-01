// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainWidget.h"


#include "Components/Button.h"
#include "UI/SugerHUD.h"

void UMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Login->OnClicked.AddDynamic(this,&UMainWidget::UMainWidget::LoginButton);
}

void UMainWidget::LoginButton()
{
	if (ASugerHUD* HUD = Cast<ASugerHUD>(GetOwningPlayer()->GetHUD()))
	{
		HUD->ShowLogin();
	}
}