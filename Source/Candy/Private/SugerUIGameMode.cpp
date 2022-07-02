// Fill out your copyright notice in the Description page of Project Settings.


#include "SugerUIGameMode.h"

#include "UI/SugerHUD.h"

ASugerUIGameMode::ASugerUIGameMode()
{
	HUDClass=ASugerHUD::StaticClass();
}
