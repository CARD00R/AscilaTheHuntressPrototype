// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ATHAscila.generated.h"

class USpringArmComponent;
class UCameraComponent;

UENUM(BlueprintType)
enum class EParentStance : uint8
{
	Eps_Standing UMETA(DisplayName = "Standing"),
	Eps_Crouching UMETA(DisplayName = "Crouching"),
	Eps_Rolling UMETA(DisplayName = "Rolling"),
	Eps_InAir UMETA(DisplayName = "InAir"),
	Eps_Dead UMETA(DisplayName = "Dead"),
	Eps_Max UMETA(DisplayName = "DefaultMax")
};
UENUM(BlueprintType)
enum class EStanceStatus : uint8
{
	Ess_StandIdling UMETA(DisplayName = "StandIdling"),
	Ess_StandWalking UMETA(DisplayName = "StandWalking"),
	Ess_StandJogging UMETA(DisplayName = "StandJogging"),
	Ess_StandSprinting UMETA(DisplayName = "StandSprinting"),
	Ess_CrouchIdling UMETA(DisplayName = "CrouchIdling"),
	Ess_CrouchWalking UMETA(DisplayName = "CrouchWalking"),
	Ess_CrouchSprinting UMETA(DisplayName = "CrouchSprinting"),
	Ess_NA UMETA(DisplayName = "NA"),
	Ess_Max UMETA(DisplayName = "DefaultMax")
};
UENUM(BlueprintType)
enum class EBowStatus : uint8
{
	Ebs_NA UMETA(DisplayName = "NA"),
	Ebs_AimingReady UMETA(DisplayName = "AimingReady"),
	Ebs_PoweringShot UMETA(DisplayName = "PoweringShot"),
	Ebs_FiringShot UMETA(DisplayName = "FiringShot"),
	Ebs_Max UMETA(DisplayName = "DefaultMax")
};
UENUM(BlueprintType)
enum class ERequestStance : uint8
{
	Ers_StandIdling UMETA(DisplayName = "StandIdling"),
	Ers_StandWalking UMETA(DisplayName = "StandWalking"),
	Ers_StandJogging UMETA(DisplayName = "StandJogging"),
	Ers_StandSprinting UMETA(DisplayName = "StandSprinting"),
	Ers_CrouchIdling UMETA(DisplayName = "CrouchIdling"),
	Ers_CrouchWalking UMETA(DisplayName = "CrouchWalking"),
	Ers_CrouchSprinting UMETA(DisplayName = "CrouchSprinting"),
	Ers_Aiming UMETA(DisplayName = "Aiming "),
	Ers_NA UMETA(DisplayName = "NA"),
	Ers_Max UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class ASCILATHEHUNTRESS_API AATHAscila : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AATHAscila();

	#pragma  region Components
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera")
		USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera")
		UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCharacterMovementComponent* CharMovementComp;

	#pragma endregion
	
	#pragma region States
	//Parent Stances
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "States")
	EParentStance ParentStance;
	void SetParentStanceStatus(EParentStance Status);
	EParentStance GetParentStanceStatus();
	
	// Stance Status
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "States")
	EStanceStatus StanceStatus;
	void SetStanceStatus(EStanceStatus Status);
	EStanceStatus GetStanceStatus();

	// Stance Status
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "States")
		EBowStatus BowStatus;
	void SetBowStatus(EBowStatus Status);
	EBowStatus GetBowStatus();
	
	// Request Stance
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "States")
	ERequestStance RequestStance;
	void SetRequestedStatus(ERequestStance RequestedStance);
	ERequestStance GetRequestedStance();
#pragma endregion

	#pragma region Weapons
	// Weapons
	void SetYaw(float NewYaw);
	void SetPitch(float NewPitch);
	float GetMaxPitch();
	float GetMinPitch();
	bool GetIsAiming();
	#pragma endregion
	
protected:
	// Called when the game starts or	when spawned
	virtual void BeginPlay() override;

	#pragma region Mesh & Capsule Variables
	// Initialisation Variables
		// Mesh Component
	FVector TargetMeshLocation = FVector(0, 0, 0);
			// Stand
	FVector StandMeshInitialiseLocation = FVector(-9, -4.5, -99.0);
	FRotator StandMeshInitialiseRotation = FRotator(0, -90, 0);
			// Crouch
	FVector CrouchMeshInitialiseLocation = FVector(-5, -4.5, -77);
	FVector CrouchSprintMeshInitialiseLocation = FVector(-20, 0, -80);
			// Capsule Component
	float StandCapsuleRadius = 24.0f;
	float StandCapsuleHalfHeight = 93;
	float CrouchCapsuleRadius = 30.0f;
	float CrouchCapsuleHalfHeight = 70.0f;
	float CrouchSprintCapsuleRadius = 30.0f;
	float CrouchSprintCapsuleHalfHeight = 75.0f;
	float TargetCapsuleRadius = 0.0f;
	float TargetCapsuleHalfHeight = 0.0f;
				// Capsule Speed Alpha changes
	float HeightAlpha = 0.02f;
	float RadiusAlpha = 0.02f;
	float LocationAlpha = 0.02f;
	UPROPERTY(EditAnywhere, Category = "Components|Capsule Properties")
	float CapsuleMeshAlpha = 0.01f;
	UPROPERTY(EditAnywhere, Category = "Components|Capsule Properties")
	float CapsuleTolerance = 0.5f;

	void CapsuleMeshPropertiesChange();
	FTimerHandle CapsuleMeshProprtiesChangeTimer;
	#pragma endregion 

	// Input
	bool bIsMovingForward = false;
	bool bIsMovingRight = false;
	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void LookRight(float value);

	#pragma region Movement Functions and Variables
	// Movement
		// Rotation
	//FRotator DefaultRotationRate = FRotator(0,1000,0);
	FRotator SprintingRotationRate = FRotator(0, 310, 0);
	void ChangeRotationRate();
		// Character Movement Speed
	void SetCharacterSpeed(float Speed);
	UPROPERTY(EditInstanceOnly, Category = "Movement Properties")
	float WalkSpeed = 130.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Properties")
	float JogSpeed = 520.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Properties")
	float SprintSpeed = 950.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Properties")
	float CrouchWalkSpeed = 175.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement Properties")
	float CrouchSprintSpeed = 600.0f;
		// Idle
	UPROPERTY(VisibleInstanceOnly, Category = "Movement Properties")
	bool bIdleCheck = true;
	void IdleCheck();
		// Sprint
	void RequestSprint();
	void Sprint();
	void SprintReleased();
		// Crouch
	void RequestCrouchChange();
	void AscilaCrouch();
	void AscilaUnCrouch();

	#pragma endregion
	
	#pragma region Weapons

	UPROPERTY(VisibleInstanceOnly, Category = "Weapon Properties")
	// Aiming
	bool bIsAiming = false;
	float Pitch;
	UPROPERTY(EditInstanceOnly, Category = "Weapon Properties")
	float MaxPitch = 50.0f;
	UPROPERTY(EditInstanceOnly, Category = "Weapon Properties")
	float MinPitch = -70.0f;
	float Yaw;
	void RequestAim();
	void RequestUnAim();
	void AimIn();
	void AimOut();
	void SetAimReadyValue();
	UPROPERTY(EditInstanceOnly, Category = "Weapon Properties")
	float AimReadyAlpha = 0.001f;
	float CurrentAimReady = 0.0f;
	FTimerHandle AimingReadyHandle; // When animation blending is finished then you are aim 'ready'
	void ChangeCameraProperties();
	FTimerHandle AimInHandle; // Camera Purposes
		
		
	// Firing
	void RequestDrawChange();
	void DrawBow();
	void UnDrawBow();
	void RequestFire();
	void Fire();
	bool bIsArrowDrawn = false;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Properties || Montages")
	UAnimMontage* DrawArrowMontage;
	#pragma endregion
	
	// Camera
	void ChangeCameraSettings();
	FVector SpringCompSocketAimOffset = FVector(0, 130.0, 80.0);
	FVector SpringCompSocketDefaultOffset = FVector(0, 130.0, 80.0);

	// Animation
	float PlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName);
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
