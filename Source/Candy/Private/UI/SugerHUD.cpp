// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SugerHUD.h"

#include "UI/MainWidget.h"
#include "UI/Widget/LoginUserWidget.h"
#include "UI/Widget/RoomListUserWidget.h"


void ASugerHUD::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<UMainWidget> MainWidgetclass = LoadClass<UMainWidget>(nullptr,TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/UI/UMG_MainUserWidget.UMG_MainUserWidget_C'"));

	if (MainWidgetclass)
	{
		MainWidget = CreateWidget<UMainWidget>(GetOwningPlayerController(),MainWidgetclass);
		
		if (MainWidget)
		{
			if (MainWidget->IsInViewport())
			{
				
			}
			MainWidget->AddToViewport();
			UE_LOG(LogTemp,Log,TEXT("+++++++++++++"))
		}
	}
	//GetOwningPlayerController()->SetShowMouseCursor(true);
}

void ASugerHUD::ShowLogin()
{
	if (!LoginUserWidget)
	{
		TSubclassOf<ULoginUserWidget> LoginUIClass = LoadClass<ULoginUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/UI/Widget/UMG_LoginUserWidget.UMG_LoginUserWidget_C'"));
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

void ASugerHUD::ShowRoomListUI()
{
	if (!RoomListUserWidget)
	{
		TSubclassOf<URoomListUserWidget> RoomListUIClass = LoadClass<URoomListUserWidget>(nullptr,TEXT("WidgetBlueprint'/Game/ThirdPersonCPP/UI/Widget/GameRoom/UMG_RoomList.UMG_RoomList_C'"));
		if (RoomListUIClass)
		{
			RoomListUserWidget = CreateWidget<URoomListUserWidget>(GetOwningPlayerController(),RoomListUIClass);
	
			if (RoomListUserWidget && !RoomListUserWidget->IsInViewport())
			{
				RoomListUserWidget->AddToViewport();
				//移除登录界面
				// LoginUserWidget->RemoveFromParent();
			}
		}
	}
}
