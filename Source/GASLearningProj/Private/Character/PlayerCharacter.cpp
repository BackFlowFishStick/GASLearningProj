// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/GASPlayerState.h"

APlayerCharacter::APlayerCharacter()
{
	// Rotate the chararcter toward the direction or acceleration.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Set Rotation per second
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// Maintain on floor
	GetCharacterMovement()->bConstrainToPlane = true;
	// On the floor since start
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Disable controller rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	// Create a camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 1200.0f;
	CameraBoom->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	CameraBoom->bDoCollisionTest = false;
	
	// Create a camera
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;// Camera does not rotate relative to arm
	
	
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the server
	InitAbilityActorInfo();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the server
	InitAbilityActorInfo();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AGASPlayerState* GASPlayerState = GetPlayerState<AGASPlayerState>();

	check(GASPlayerState);

	GASPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(GASPlayerState, this);

	AbilitySystemComponent = GASPlayerState->GetAbilitySystemComponent();

	AttributeSet = GASPlayerState->GetAttributeSet();
}


