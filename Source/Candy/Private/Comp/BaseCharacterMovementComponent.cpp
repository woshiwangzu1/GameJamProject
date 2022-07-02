// Fill out your copyright notice in the Description page of Project Settings.


#include "Comp/BaseCharacterMovementComponent.h"

#include "Candy/CandyCharacter.h"

float UBaseCharacterMovementComponent::GetMaxSpeed() const
{
	if (ACandyCharacter* CandyCharacter = Cast<ACandyCharacter>(GetPawnOwner()))
	{
		if (CandyCharacter->IsGetHit())
		{
			return 0;
		}
		
	}

	return Super::GetMaxSpeed();
	
}
