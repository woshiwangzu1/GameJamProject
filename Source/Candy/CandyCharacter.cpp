// Copyright Epic Games, Inc. All Rights Reserved.

#include "CandyCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Comp/BaseCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

//////////////////////////////////////////////////////////////////////////
// ACandyCharacter


ACandyCharacter::ACandyCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UBaseCharacterMovementComponent>(CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	bRagdollOnGround = true;
	HitDownTime = 2.f;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}



void ACandyCharacter::GetHit()
{
	if (HasAuthority())
	{
		Multi_GetHit();
	}else
	{
		Server_GetHit();
	}
}



void ACandyCharacter::Server_GetHit_Implementation()
{
	Multi_GetHit();
}

bool ACandyCharacter::Server_GetHit_Validate()
{
	return true;
}

void ACandyCharacter::Multi_GetHit_Implementation()
{
	PlayAnimMontage(HitDownMontage);
	bIsGetHit = true;
	CurrentHitDownTime = HitDownTime;
}

bool ACandyCharacter::Multi_GetHit_Validate()
{
	return true;
}

void ACandyCharacter::GetUp()
{
	if (HasAuthority())
	{
		Multi_GetUp();
	}else
	{
		Server_GetUp();
	}
}

void ACandyCharacter::Server_GetUp_Implementation()
{
	Multi_GetUp();
}

bool ACandyCharacter::Server_GetUp_Validate()
{
	return true;
}

void ACandyCharacter::Multi_GetUp_Implementation()
{
	PlayAnimMontage(GetUpMontage);
	bIsGetHit = false;
}

bool ACandyCharacter::Multi_GetUp_Validate()
{
	return true;
}

void ACandyCharacter::Kick()
{
	return;
	if (bIsGetHit)
	{
		return;
	}
	PlayAnimMontage(AttackMontage);
}

void ACandyCharacter::Jump()
{
	if (bIsGetHit)
	{
		return;
	}
	Super::Jump();
}

void ACandyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bIsGetHit)
	{
		CurrentHitDownTime-=DeltaSeconds;
		if (CurrentHitDownTime<=0)
		{
			GetUp();
			
		}
	}
	
}

void ACandyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// DOREPLIFETIME(ACandyCharacter,TargetRotation);
	DOREPLIFETIME(ACandyCharacter,bIsRagDoll);
	DOREPLIFETIME(ACandyCharacter,bIsGetHit);
	DOREPLIFETIME(ACandyCharacter,CurrentHitDownTime);
	// DOREPLIFETIME(ACandyCharacter,MainAnimInstance);
	// DOREPLIFETIME(ACandyCharacter,bRagdollOnGround);
	// DOREPLIFETIME(ACandyCharacter,bRagdollFaceUp);
	// DOREPLIFETIME(ACandyCharacter,LastRagdollVelocity);
	// DOREPLIFETIME(ACandyCharacter,TargetRagdollLocation);
	// DOREPLIFETIME(ACandyCharacter,TargetRagdollRotation);
}

void ACandyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACandyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACandyCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACandyCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACandyCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACandyCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ACandyCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("Kick", IE_Pressed, this, &ACandyCharacter::Kick);

	
}


void ACandyCharacter::BeginPlay()
{
	Super::BeginPlay();
	MainAnimInstance = GetMesh()->GetAnimInstance();
}

bool ACandyCharacter::IsGetHit()
{
	return bIsGetHit;
}

void ACandyCharacter::ChangeRagDoll()
{
	if (bIsRagDoll)
	{
		EndRagDoll();
	}else
	{
		StartRagDoll();
	}
}



void ACandyCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ACandyCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ACandyCharacter::StartRagDoll()
{
	if (HasAuthority())
	{
		Multi_StartRagDoll();
	}else
	{
		Server_StartRagDoll();
	}
	
}

void ACandyCharacter::Server_StartRagDoll_Implementation()
{
	Multi_StartRagDoll();
}

bool ACandyCharacter::Server_StartRagDoll_Validate()
{
	return true;
}

void ACandyCharacter::Multi_StartRagDoll_Implementation()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(TEXT("J_Bip_C_Hips"), true);
	GetMesh()->GetAnimInstance()->Montage_Stop(0.2f);
	bIsRagDoll = true;
}

bool ACandyCharacter::Multi_StartRagDoll_Validate()
{
	return true;
}

void ACandyCharacter::EndRagDoll()
{
	if (HasAuthority())
	{
		Multi_EndRagDoll();
	}else
	{
		Server_EndRagDoll();
	}
}

void ACandyCharacter::Multi_EndRagDoll_Implementation()
{
	MainAnimInstance->SavePoseSnapshot(TEXT("RagdollPose"));
	if (bRagdollOnGround)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		MainAnimInstance->Montage_Play(GetGetUpMontage(bRagdollFaceUp));
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
		GetCharacterMovement()->Velocity = LastRagdollVelocity;
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetAllBodiesSimulatePhysics(false);
	bIsRagDoll = false;

	UpdateRagDoll();
}

bool ACandyCharacter::Multi_EndRagDoll_Validate()
{
	return true;
}

void ACandyCharacter::Server_EndRagDoll_Implementation()
{
	Multi_EndRagDoll();
}

bool ACandyCharacter::Server_EndRagDoll_Validate()
{
	return true;
}

void ACandyCharacter::UpdateRagDoll()
{
	if (!HasAuthority())
	{
		return;
	}
	LastRagdollVelocity = GetMesh()->GetPhysicsLinearVelocity(TEXT("J_Bip_C_Hips"));
	float VectorLength = UKismetMathLibrary::VSize(LastRagdollVelocity);
	float ClampedRange = UKismetMathLibrary::MapRangeClamped(VectorLength,0,1000,0,25000);

	GetMesh()->SetAllMotorsAngularDriveParams(ClampedRange,0,0,false);

	//控制下落速度
	GetMesh()->SetEnableGravity(LastRagdollVelocity.Z>-4000);

	
	TargetRagdollLocation = GetMesh()->GetSocketLocation("J_Bip_C_Hips");
	
	bRagdollFaceUp = GetMesh()->GetSocketRotation(TEXT("J_Bip_C_Hips")).Roll<0;
	FRotator Rotator;
	if (bRagdollFaceUp)
	{
		Rotator.Yaw = GetMesh()->GetSocketRotation(TEXT("J_Bip_C_Hips")).Yaw-180;
	}else
	{
		Rotator.Yaw = GetMesh()->GetSocketRotation(TEXT("J_Bip_C_Hips")).Yaw;
	}
	TargetRagdollRotation = Rotator;

	FVector EndLocation;
	EndLocation.X = TargetRagdollLocation.X;
	EndLocation.Y = TargetRagdollLocation.Y;
	EndLocation.Z = TargetRagdollLocation.Z-GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	UKismetSystemLibrary::LineTraceSingle(this,TargetRagdollLocation,EndLocation,
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),false, ActorsToIgnore, EDrawDebugTrace::None,HitResult,true);

	bRagdollOnGround = HitResult.bBlockingHit;
	if (bRagdollOnGround)
	{
		FVector NewLocation;
		TargetRotation = TargetRagdollRotation;
		NewLocation.X = TargetRagdollLocation.X;
		NewLocation.Y = TargetRagdollLocation.Y;
		NewLocation.Z = TargetRagdollLocation.Z
		+GetCapsuleComponent()->GetScaledCapsuleHalfHeight()
		-UKismetMathLibrary::Abs(HitResult.ImpactPoint.Z-HitResult.TraceStart.Z)
		+2;
		SetActorLocationAndRotation(NewLocation,TargetRagdollRotation);
		
	}else
	{
		SetActorLocationAndRotation(TargetRagdollLocation,TargetRagdollRotation);
	}
}

void ACandyCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACandyCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACandyCharacter::MoveForward(float Value)
{
	if (bIsGetHit)
	{
		return;
	}
	
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACandyCharacter::MoveRight(float Value)
{
	if (bIsGetHit)
	{
		return;
	}
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
