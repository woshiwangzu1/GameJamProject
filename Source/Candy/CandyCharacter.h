// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CandyCharacter.generated.h"
UCLASS(config=Game)
class ACandyCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	
public:
	ACandyCharacter(const FObjectInitializer& ObjectInitializer);

	

	virtual void BeginPlay() override;

	
	bool IsGetHit();

	UFUNCTION(BlueprintCallable)
	void GetHit();
	
protected:

	/** Resets HMD orientation in VR. */
	void ChangeRagDoll();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	UFUNCTION(BlueprintCallable)
	void StartRagDoll();
	UFUNCTION(Reliable,Server,WithValidation)
	void Server_StartRagDoll();
	UFUNCTION(Reliable,NetMulticast,WithValidation)
	void Multi_StartRagDoll();
	
	UFUNCTION(BlueprintCallable)
	void EndRagDoll();

	UFUNCTION(Reliable,NetMulticast,WithValidation)
	void Multi_EndRagDoll();

	UFUNCTION(Reliable,Server,WithValidation)
	void Server_EndRagDoll();
	
	UFUNCTION(BlueprintCallable)
	void UpdateRagDoll();

	
	UFUNCTION(BlueprintImplementableEvent)
	UAnimMontage* GetGetUpMontage(bool RagDollFaceUp);
	
	UFUNCTION(Reliable,Server,WithValidation)
	void Server_GetHit();
	UFUNCTION(Reliable,NetMulticast,WithValidation)
	void Multi_GetHit();

	UFUNCTION(BlueprintCallable)
	void GetUp();
	UFUNCTION(Reliable,Server,WithValidation)
	void Server_GetUp();
	UFUNCTION(Reliable,NetMulticast,WithValidation)
	void Multi_GetUp();
	
	void Kick();

	void Jump() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
protected:
	UPROPERTY(Replicated,BlueprintReadWrite)
	uint8 bIsRagDoll:1;
	UPROPERTY(Replicated,BlueprintReadWrite)
	uint8 bIsGetHit:1;
	
	UPROPERTY(BlueprintReadWrite)
	UAnimInstance* MainAnimInstance;
	UPROPERTY(BlueprintReadWrite)
	uint8 bRagdollOnGround:1;
	UPROPERTY(BlueprintReadWrite)
	uint8 bRagdollFaceUp:1;
	UPROPERTY(BlueprintReadWrite)
	FVector LastRagdollVelocity;
	UPROPERTY(EditAnywhere)
	FVector TargetRagdollLocation;
	UPROPERTY(EditAnywhere)
	FRotator TargetRagdollRotation;
	UPROPERTY(BlueprintReadWrite)
	FRotator TargetRotation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* HitDownMontage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* GetUpMontage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere)
	float HitDownTime;
	UPROPERTY(Replicated)
	float CurrentHitDownTime;
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
};

