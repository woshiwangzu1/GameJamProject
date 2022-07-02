// Fill out your copyright notice in the Description page of Project Settings.


#include "Animnotify/PlayerAttackAnimNotify.h"

#include "Candy/CandyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void UPlayerAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (ACandyCharacter* Character = Cast<ACandyCharacter>(MeshComp->GetOwner()))
	{
		TArray<AActor*> ActorsToIgnore;
		FHitResult HitResult;
		UKismetSystemLibrary::SphereTraceSingle(MeshComp->GetOwner(),Character->GetActorLocation(),Character->GetActorLocation(),
			150.f,UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_WorldDynamic),false,ActorsToIgnore,EDrawDebugTrace::None,
			HitResult,true);
		UE_LOG(LogTemp, Log, TEXT("Try Trace"));
		if (HitResult.bBlockingHit)
		{
			
			UE_LOG(LogTemp, Log, TEXT("isHit====%s"),*HitResult.Actor->GetName());
			if (ACandyCharacter* OtherCharacter = Cast<ACandyCharacter>(HitResult.Actor))
			{
				OtherCharacter->GetHit();
			}
			
			
		}
	}
}
