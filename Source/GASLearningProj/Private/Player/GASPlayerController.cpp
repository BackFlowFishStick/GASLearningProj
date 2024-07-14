// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GASPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AGASPlayerController::AGASPlayerController()
{
	bReplicates = true;
}

void AGASPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	
}

void AGASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Check whether the object is valid or not, it is a UE macro.
	check(GasContext);

	//UEnhancedInputLocalPlayerSubsystem
	auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(subSystem);

	subSystem->AddMappingContext(GasContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AGASPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGASPlayerController::Move);
}

void AGASPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2d>();

	const FRotator rotation = GetControlRotation();

	const FRotator YawRotation(0.0f, rotation.Yaw, 0.0f);

	const FVector forwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* controlledPawn = GetPawn<APawn>())
	{
		controlledPawn->AddMovementInput(forwardDir, InputAxisVector.Y);
		controlledPawn->AddMovementInput(rightDir, InputAxisVector.X);
	} 
}

void AGASPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = CursorHit.GetActor();

	/*
	 * A. LastActor is null && CurrentActor is null
	 * -- Do nothing
	 * B. LastActor is null && CurrentActor is valid
	 * -- Highlight CurrentActor
	 * C. LastActor is valid && CurrentActor is null
	 * -- UnHighlight LastActor
	 * D. LastActor is valid && CurrentActor is valid && LastActor != CurrentActor
	 * -- UnHighlight LastActor, then Highlight CurrentActor
	 * E. Both actors are valid, and they are the same actor
	 * -- Do nothing
	 */
	if(LastActor == nullptr && CurrentActor == nullptr)
	{
		// Case A
		return;
	}

	if(LastActor == CurrentActor)
	{
		// Case E
		return;
	}

	if(LastActor == nullptr && CurrentActor != nullptr)
	{
		// Case B
		CurrentActor->HighlightActor();
		return;
	}

	if(LastActor != nullptr && CurrentActor == nullptr)
	{
		// Case C
		LastActor->UnHighlightActor();
		return;
	}

	if(LastActor != nullptr && CurrentActor != nullptr && LastActor != CurrentActor)
	{
		// Case D
		LastActor->UnHighlightActor();
		CurrentActor->HighlightActor();
		return;
	}
	
}


