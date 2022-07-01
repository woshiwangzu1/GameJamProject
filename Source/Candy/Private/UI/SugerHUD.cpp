// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SugerHUD.h"

#include "UI/MainWidget.h"
#include "UI/Widget/LoginUserWidget.h"


void ASugerHUD::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<UMainWidget> MainWidgetclass = LoadClass<UMainWidget>(nullptr,TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/UserWidget/UMG_MainUserWidget.UMG_MainUserWidget_C'"));

	if (MainWidgetclass)
	{
		UMainWidget* MainWidget = CreateWidget<UMainWidget>(GetOwningPlayerController(),MainWidgetclass);

		if (MainWidget)
		{
			MainWidget->AddToViewport();
		}
	}
	GetOwningPlayerController()->SetShowMouseCursor(true);
}

void ASugerHUD::ShowLogin()
{
	if (!LoginUserWidget)
	{
		TSubclassOf<ULoginUserWidget> LoginUIClass = LoadClass<ULoginUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/UserWidget/Widget/UMG_LoginUserWidget.UMG_LoginUserWidget_C'"));
		if (LoginUIClass)
		{
			LoginUserWidget = CreateWidget<ULoginUserWidget>(GetOwningPlayerController(),LoginUIClass);
	
			if (LoginUserWidget && !LoginUserWidget->IsInViewport())
			{
				LoginUserWidget->AddToViewport();
			}
		}
	}
	
}
