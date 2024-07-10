// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GASPlayerController.h"

#include "EnhancedInputSubsystems.h"

AGASPlayerController::AGASPlayerController()
{
	bReplicates = true;
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
